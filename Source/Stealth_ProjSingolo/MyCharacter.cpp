// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/Controller.h"
#include "MyEnemyReal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Stealth_ProjSingoloGameMode.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	AttackCheckLocation = CreateDefaultSubobject<USceneComponent>("AttackCheckPos");
	AttackCheckLocation->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	AStealth_ProjSingoloGameMode* GameMode = Cast<AStealth_ProjSingoloGameMode>(GameModeBase);
	GameMode->SetPlayer(this);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AMyCharacter::PlayerCrouch);
		EnhancedInputComponent->BindAction(Move, ETriggerEvent::Triggered, this, &AMyCharacter::MovePlayer);
		EnhancedInputComponent->BindAction(MoveCamera, ETriggerEvent::Triggered, this, &AMyCharacter::MovePlayerCamera);
	}
}

void AMyCharacter::MovePlayer(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMyCharacter::MovePlayerCamera(const FInputActionValue& Value)
{
	FVector2D AxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(AxisVector.X);
		AddControllerPitchInput(AxisVector.Y);
	}
}

void AMyCharacter::PlayerCrouch(const FInputActionValue& Value)
{
	if (CanCrouch())
		Crouch();
	else
		UnCrouch();
}

void AMyCharacter::Attack(const FInputActionValue& Value)
{
	if (GetCharacterMovement()->IsFalling()) return;

	FHitResult OutHit;

	FVector TraceLocationStart = AttackCheckLocation->GetComponentLocation();
	FVector TraceLocationEnd = TraceLocationStart + GetActorForwardVector() * AttackCheckLenght;

	FCollisionObjectQueryParams ObjParams;
	ObjParams.AddObjectTypesToQuery(ECC_GameTraceChannel1);

	FCollisionQueryParams TraceParams;

	if (!GetWorld()->LineTraceSingleByObjectType(OutHit, TraceLocationStart, TraceLocationEnd, ObjParams, TraceParams))
	{
		DrawDebugLine(GetWorld(), TraceLocationStart, TraceLocationEnd, FColor::Red, true, 5, 0, 5);
		return;
	}

	DrawDebugLine(GetWorld(), TraceLocationStart, TraceLocationEnd, FColor::Green, true, 5, 0, 5);

	AActor* HitActor = OutHit.GetActor();
	AMyEnemyReal* Enemy = Cast<AMyEnemyReal>(HitActor);
	const UBlackboardComponent* EnemyBlackBoard = Enemy->GetBlackBoardComponent();

	if (!Enemy->CanBeAttacked()) return;
	Enemy->ReceiveAttack();

	UnCrouch();
	SetActorEnableCollision(false);

	FTransform BehindEnemyTransform;
	GetBehindEnemyTransform(BehindEnemyTransform, Enemy);
	SetActorTransform(BehindEnemyTransform);

	IsAttacking = true;

	DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AMyCharacter::GetBehindEnemyTransform(FTransform& BehindTransform, AMyEnemyReal* Enemy)
{
	FTransform EnemyTransform = Enemy->GetActorTransform();

	FVector BehindPlayerLocation;
	FVector EnemyLocation = EnemyTransform.GetLocation();
	FVector EnemyForward = Enemy->GetActorForwardVector();

	BehindPlayerLocation = (EnemyForward * -165) + EnemyLocation;
	BehindTransform.SetLocation(BehindPlayerLocation);

	FQuat EnemyRotator = EnemyTransform.GetRotation();
	BehindTransform.SetRotation(EnemyRotator);
}

void AMyCharacter::ReceiveAttack()
{
	this->DisableInput(nullptr);
	GetMesh()->SetVisibility(false);

	OnPlayerDeath.Execute();
}