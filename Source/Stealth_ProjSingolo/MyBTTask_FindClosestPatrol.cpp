// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindClosestPatrol.h"
#include "MyEnemyAIController.h"
#include "NavigationSystem.h"
#include "MyEnemyReal.h"
#include "MyAIBehaviorComponent.h"
#include "MyPatrolPoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UMyBTTask_FindClosestPatrol::UMyBTTask_FindClosestPatrol(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Closest Patrol Point";
}

EBTNodeResult::Type UMyBTTask_FindClosestPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController)) return EBTNodeResult::Failed;

	const APawn* AIPawn = AIController->GetPawn();
	const AMyEnemyReal* AICharacter = Cast<AMyEnemyReal>(AIPawn);
	if (!IsValid(AICharacter)) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackBoardComponent = OwnerComp.GetBlackboardComponent();

	const UMyAIBehaviorComponent* AIBehaviourComponent = AICharacter->GetAIBehaviourComponent();
	TConstArrayView<AMyPatrolPoint*> PatrolPath = AIBehaviourComponent->GetPatrolPath();

	FVector AILocation = AIPawn->GetActorLocation();
	float ClosestDistance = BIG_NUMBER;
	AMyPatrolPoint* ClosestPatrolPoint = nullptr;
	for (AMyPatrolPoint* PatrolPoint : PatrolPath)
	{
		FVector PatrolPointLocation = PatrolPoint->GetActorLocation();
		float CurrentDistance = UKismetMathLibrary::Vector_DistanceSquared(AILocation, PatrolPointLocation);

		if (ClosestDistance > CurrentDistance)
		{
			ClosestDistance = CurrentDistance;
			ClosestPatrolPoint = PatrolPoint;
		}
	}

	BlackBoardComponent->SetValueAsObject(GetSelectedBlackboardKey(), ClosestPatrolPoint);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
