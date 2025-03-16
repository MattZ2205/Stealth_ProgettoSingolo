// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Stealth_ProjSingoloGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "MyFinish.h"
#include "MyWidget.h"


void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	AStealth_ProjSingoloGameMode* GameMode = Cast<AStealth_ProjSingoloGameMode>(GameModeBase);
	GameMode->OnGameOver.AddUniqueDynamic(this, &AMyHUD::Handle_OnGameOver);
}

void AMyHUD::Handle_OnGameOver(bool IsPlayerWon)
{
	UUserWidget* WidgetGameOver = nullptr;

	if (IsPlayerWon)
		WidgetGameOver = CreateWidget<UUserWidget>(GetWorld(), WidgetWonClass);
	else
		WidgetGameOver = CreateWidget<UUserWidget>(GetWorld(), WidgetDeathClass);

	WidgetGameOver->AddToViewport();
}