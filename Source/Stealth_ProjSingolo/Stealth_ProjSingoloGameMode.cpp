// Copyright Epic Games, Inc. All Rights Reserved.

#include "Stealth_ProjSingoloGameMode.h"
#include "Stealth_ProjSingoloCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "MyFinish.h"

AStealth_ProjSingoloGameMode::AStealth_ProjSingoloGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AStealth_ProjSingoloGameMode::ReloadLevel()
{
	FTimerHandle TimerHandle;

	FTimerDynamicDelegate TimerDelegate;
	TimerDelegate.BindDynamic(this, &AStealth_ProjSingoloGameMode::Handle_TimerEnded);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 5, false);
}

void AStealth_ProjSingoloGameMode::Handle_TimerEnded()
{
	FString LevelString = UGameplayStatics::GetCurrentLevelName(GetWorld());
	FName LevelName = FName(LevelString);
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void AStealth_ProjSingoloGameMode::SetFinish(AMyFinish* NewEnd)
{
	NewEnd->OnFinishReached.BindDynamic(this, &AStealth_ProjSingoloGameMode::Handle_GameWon);
}

void AStealth_ProjSingoloGameMode::SetPlayer(AMyCharacter* NewPlayerCharacter)
{
	NewPlayerCharacter->OnPlayerDeath.BindDynamic(this, &AStealth_ProjSingoloGameMode::Handle_GameLost);
}

void AStealth_ProjSingoloGameMode::Handle_GameWon()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)	PlayerPawn->DisableInput(nullptr);

	OnGameOver.Broadcast(true);
	ReloadLevel();
}

void AStealth_ProjSingoloGameMode::Handle_GameLost()
{
	OnGameOver.Broadcast(false);
	ReloadLevel();
}
