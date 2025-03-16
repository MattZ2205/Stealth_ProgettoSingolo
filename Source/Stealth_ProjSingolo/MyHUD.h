// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 *
 */
UCLASS()
class STEALTH_PROJSINGOLO_API AMyHUD : public AHUD
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

	UFUNCTION()
	void Handle_OnGameOver(bool IsPlayerWon);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> WidgetDeathClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> WidgetWonClass;
};
