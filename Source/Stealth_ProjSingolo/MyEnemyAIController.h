// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyEnemyAIController.generated.h"

class UAIPerceptionComponent;

UCLASS()
class STEALTH_PROJSINGOLO_API AMyEnemyAIController : public AAIController
{
	GENERATED_BODY()

	AMyEnemyAIController();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void Handle_OnPerceptionUpdated(AActor* TargetActor, FAIStimulus Stimulus);

	UPROPERTY(EditAnywhere)
	bool IsBeingSpotted;

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* BTEnemy;
};
