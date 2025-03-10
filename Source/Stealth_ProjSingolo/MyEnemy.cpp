// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEnemy.h"
#include "MyAIBehaviorComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyEnemy::AMyEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AIBehaviorComponent = CreateDefaultSubobject<UMyAIBehaviorComponent>("AI Behaviour");
}

void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();

	BlackBoardComponent = UAIBlueprintHelperLibrary::GetBlackboard(this);

	//UE_LOG(LogTemp, Warning, TEXT(BlackBoardComponent.GetName()));
}

void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyEnemy::Attack(APawn* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy Attack!"));
}

void AMyEnemy::ReceiveAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy Receive Attack!"));
}