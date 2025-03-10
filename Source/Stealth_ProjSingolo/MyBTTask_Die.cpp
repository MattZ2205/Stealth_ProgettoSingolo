// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Die.h"
#include "AIController.h"

UMyBTTask_Die::UMyBTTask_Die(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Die";
}


EBTNodeResult::Type UMyBTTask_Die::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIOwner->GetPawn();
	AIPawn->Destroy();

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}