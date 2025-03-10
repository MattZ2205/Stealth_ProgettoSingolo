// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindNextPatrolPoint.h"
#include "MyEnemyAIController.h"
#include "NavigationSystem.h"
#include "MyEnemy.h"
#include "MyAIBehaviorComponent.h"
#include "MyPatrolPoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_FindNextPatrolPoint::UMyBTTask_FindNextPatrolPoint(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Next Patrol Point";
}

EBTNodeResult::Type UMyBTTask_FindNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController)) return EBTNodeResult::Failed;

	const APawn* AIPawn = AIController->GetPawn();
	const AMyEnemy* AICharacter = Cast<AMyEnemy>(AIPawn);
	if (!IsValid(AICharacter)) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackBoardComponent = OwnerComp.GetBlackboardComponent();

	const UMyAIBehaviorComponent* AIBehaviorComponent = AICharacter->GetAIBehaviourComponent();

	AMyPatrolPoint* PatrolPoint = Cast<AMyPatrolPoint>(BlackBoardComponent->GetValueAsObject(GetSelectedBlackboardKey()));
	AIBehaviorComponent->UpdateToNextPatrolPoint(PatrolPoint);
	FVector NextLocation = PatrolPoint->GetActorLocation();

	BlackBoardComponent->SetValueAsObject(GetSelectedBlackboardKey(), PatrolPoint);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}