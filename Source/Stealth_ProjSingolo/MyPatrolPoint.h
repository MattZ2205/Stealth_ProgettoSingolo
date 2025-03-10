// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPatrolPoint.generated.h"

UCLASS()
class STEALTH_PROJSINGOLO_API AMyPatrolPoint : public AActor
{
	GENERATED_BODY()

public:
	AMyPatrolPoint();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BlueprintProtected))
	UMeshComponent* MeshComponent;
};
