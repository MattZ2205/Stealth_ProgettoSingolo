// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTask_Forget.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_Forget::UMyBTTask_Forget(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Forget";
}

EBTNodeResult::Type UMyBTTask_Forget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoardComponent = OwnerComp.GetBlackboardComponent();

	BlackBoardComponent->ClearValue(GetSelectedBlackboardKey());
	BlackBoardComponent->ClearValue(BlackboardKey2.SelectedKeyName);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}