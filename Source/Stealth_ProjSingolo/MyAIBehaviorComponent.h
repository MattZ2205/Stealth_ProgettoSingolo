// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyAIBehaviorComponent.generated.h"

class APatrolPoint;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STEALTH_PROJSINGOLO_API UMyAIBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMyAIBehaviorComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BlueprintProtected));
	TArray<AMyPatrolPoint*> PatrolPath;

public:
	TConstArrayView<AMyPatrolPoint*> GetPatrolPath() const { return PatrolPath; }

	UFUNCTION(BlueprintCallable)
	void UpdateToNextPatrolPoint(AMyPatrolPoint*& CurrentPatrolPoint) const;
};

