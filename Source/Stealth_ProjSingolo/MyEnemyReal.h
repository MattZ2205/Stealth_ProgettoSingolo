// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEnemyReal.generated.h"

class UMyAIBehaviorComponent;
class UBlackboardComponent;

UCLASS()
class STEALTH_PROJSINGOLO_API AMyEnemyReal : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyEnemyReal();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BlueprintProtected))
	UMyAIBehaviorComponent* AIBehaviorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BlueprintProtected))
	UBlackboardComponent* BlackBoardComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Attack(APawn* Entity);

	UFUNCTION()
	void ReceiveAttack();

	const UMyAIBehaviorComponent* GetAIBehaviourComponent() const { return AIBehaviorComponent; };
	const UBlackboardComponent* GetBlackBoardComponent() const { return BlackBoardComponent; };
};
