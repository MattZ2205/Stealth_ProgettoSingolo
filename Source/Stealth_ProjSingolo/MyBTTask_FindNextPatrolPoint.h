// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_FindNextPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class STEALTH_PROJSINGOLO_API UMyBTTask_FindNextPatrolPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()


protected:
	explicit UMyBTTask_FindNextPatrolPoint(FObjectInitializer const& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
