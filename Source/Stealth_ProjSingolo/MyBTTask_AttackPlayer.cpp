// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_AttackPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyCharacter.h"
#include "MyEnemyReal.h"
#include "MyEnemyAIController.h"

UMyBTTask_AttackPlayer::UMyBTTask_AttackPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Attack Player";
}

EBTNodeResult::Type UMyBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoardComponent = OwnerComp.GetBlackboardComponent();

	UObject* PlayerObj = BlackBoardComponent->GetValueAsObject(GetSelectedBlackboardKey());
	AMyCharacter* Player = Cast<AMyCharacter>(PlayerObj);
	UE_LOG(LogTemp, Warning, TEXT("LOG PORCODDIO"));
	if (!IsValid(Player))
	{
		UE_LOG(LogTemp, Error, TEXT("Player is not valid"));
		return EBTNodeResult::Failed;
	}
	UE_LOG(LogTemp, Warning, TEXT("Player: %s"), *Player->GetName());

	//Player->ReceiveAttack();

	AMyEnemyAIController* AIController = Cast<AMyEnemyAIController>(OwnerComp.GetAIOwner());
	ACharacter* AICharacter = AIController->GetCharacter();
	AMyEnemyReal* Enemy = Cast<AMyEnemyReal>(AICharacter);

	Enemy->Attack(Player);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}