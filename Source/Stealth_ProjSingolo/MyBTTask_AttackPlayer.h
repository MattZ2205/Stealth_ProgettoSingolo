// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_AttackPlayer.generated.h"

/**
 *
 */
UCLASS()
class STEALTH_PROJSINGOLO_API UMyBTTask_AttackPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:
	explicit UMyBTTask_AttackPlayer(FObjectInitializer const& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
