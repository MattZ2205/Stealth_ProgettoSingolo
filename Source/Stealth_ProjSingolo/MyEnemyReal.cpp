// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyReal.h"
#include "MyAIBehaviorComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyCharacter.h"

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

void AMyEnemyReal::Attack(AMyCharacter* Player)
{
	IsAttacking = true;
	Player->ReceiveAttack();
}

void AMyEnemyReal::ReceiveAttack()
{
	BlackBoardComponent->SetValueAsBool("IsBeingAttacked", true);
	SetActorEnableCollision(false);
}

bool AMyEnemyReal::CanBeAttacked()
{
	FName PlayerBlackboardKey = "Player";
	FName StimulusLocationBlackboardKey = "StimulusLocation";

	//If the enemy doesnt even suspect that the player is around, we can kill him 100%
	UObject* Player = BlackBoardComponent->GetValueAsObject(PlayerBlackboardKey);
	if (!IsValid(Player)) return true;

	//If the enemy knows the player is around we check if its investigating or its a direct contact.
	bool IsInvestigating = BlackBoardComponent->IsVectorValueSet(StimulusLocationBlackboardKey);
	if (IsInvestigating) return true;

	return false;
}