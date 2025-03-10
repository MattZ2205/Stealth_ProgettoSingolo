// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_Forget.generated.h"

/**
 *
 */
UCLASS()
class STEALTH_PROJSINGOLO_API UMyBTTask_Forget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector BlackboardKey2;

protected:
	explicit UMyBTTask_Forget(FObjectInitializer const& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
