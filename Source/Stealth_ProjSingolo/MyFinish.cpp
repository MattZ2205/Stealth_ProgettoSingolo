// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFinish.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Stealth_ProjSingoloGameMode.h"

// Sets default values
AMyFinish::AMyFinish()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCheck = CreateDefaultSubobject<UBoxComponent>("Goal Collision Check");
	SetRootComponent(BoxCheck);
}

// Called when the game starts or when spawned
void AMyFinish::BeginPlay()
{
	Super::BeginPlay();

	BoxCheck->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMyFinish::OnBoxBeginOverlap);

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	AStealth_ProjSingoloGameMode* GameMode = Cast<AStealth_ProjSingoloGameMode>(GameModeBase);
	GameMode->SetFinish(this);
}

// Called every frame
void AMyFinish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyFinish::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)	PlayerPawn->DisableInput(nullptr);

	OnFinishReached.Execute();
}