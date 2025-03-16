// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFinish.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE(FOnFinishReached);

class UBoxComponent;

UCLASS()
class STEALTH_PROJSINGOLO_API AMyFinish : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FOnFinishReached OnFinishReached;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UBoxComponent* BoxCheck;

public:
	AMyFinish();

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void Tick(float DeltaTime) override;
};
