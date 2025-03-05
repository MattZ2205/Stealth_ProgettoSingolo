// Copyright Epic Games, Inc. All Rights Reserved.

#include "Stealth_ProjSingoloGameMode.h"
#include "Stealth_ProjSingoloCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStealth_ProjSingoloGameMode::AStealth_ProjSingoloGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
