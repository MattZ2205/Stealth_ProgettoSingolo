// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_AttackPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyCharacter.h"
#include "MyEnemy.h"

UMyBTTask_AttackPlayer::UMyBTTask_AttackPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Attack Player";
}

EBTNodeResult::Type UMyBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoardComponent = OwnerComp.GetBlackboardComponent();

	UObject* PlayerObj = BlackBoardComponent->GetValueAsObject(GetSelectedBlackboardKey());
	AMyCharacter* Player = Cast<AMyCharacter>(PlayerObj);
	if (!IsValid(Player)) return EBTNodeResult::Failed;

	Player->ReceiveAttack();

	AAIController* AIController = OwnerComp.GetAIOwner();
	ACharacter* AICharacter = AIController->GetCharacter();
	AMyEnemy* Enemy = Cast<AMyEnemy>(AICharacter);

	Enemy->Attack(Player);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}