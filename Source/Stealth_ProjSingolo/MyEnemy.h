// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyEnemy.generated.h"

class UMyAIBehaviorComponent;
class UBlackboardComponent;

UCLASS()
class STEALTH_PROJSINGOLO_API AMyEnemy : public APawn
{
	GENERATED_BODY()

public:
	AMyEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BlueprintProtected))
	UMyAIBehaviorComponent* AIBehaviorComponent;

	UPROPERTY(BlueprintReadOnly, meta = (BlueprintProtected))
	UBlackboardComponent* BlackBoardComponent;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Attack(APawn* Entity);

	UFUNCTION()
	void ReceiveAttack();

	const UMyAIBehaviorComponent* GetAIBehaviourComponent() const { return AIBehaviorComponent; };
	const UBlackboardComponent* GetBlackBoardComponent() const { return BlackBoardComponent; };
};
