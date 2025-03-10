// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyReal.h"
#include "MyAIBehaviorComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AMyEnemyReal::AMyEnemyReal()
{
	PrimaryActorTick.bCanEverTick = true;

	AIBehaviorComponent = CreateDefaultSubobject<UMyAIBehaviorComponent>("AI Behaviour");
}

// Called when the game starts or when spawned
void AMyEnemyReal::BeginPlay()
{
	Super::BeginPlay();

	BlackBoardComponent = UAIBlueprintHelperLibrary::GetBlackboard(this);
}

// Called every frame
void AMyEnemyReal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyEnemyReal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyEnemyReal::Attack(APawn* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy Attack!"));
}

void AMyEnemyReal::ReceiveAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy Receive Attack!"));
}