// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyCharacter.h"
#include "MyFinish.h"
#include "Stealth_ProjSingoloGameMode.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOver, bool, PlayerWon);

UCLASS(minimalapi)
class AStealth_ProjSingoloGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnGameOver OnGameOver;

private:
	FTimerHandle NextTickTimer;

protected:
	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected))
	void ReloadLevel();

	UFUNCTION()
	void Handle_TimerEnded();

public:
	UFUNCTION(BlueprintCallable)
	void SetFinish(AMyFinish* NewEnd);
	UFUNCTION(BlueprintCallable)
	void SetPlayer(AMyCharacter* NewPlayer);

protected:
	UFUNCTION(meta = (BlueprintProtected))
	void Handle_GameWon();
	UFUNCTION(meta = (BlueprintProtected))
	void Handle_GameLost();

public:
	AStealth_ProjSingoloGameMode();
};



