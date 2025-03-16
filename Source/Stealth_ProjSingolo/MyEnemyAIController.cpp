// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "MyFinish.h"
#include "MyCharacter.h"
#include "Stealth_ProjSingoloGameMode.h"

AMyEnemyAIController::AMyEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
}

void AMyEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AMyEnemyAIController::Handle_OnPerceptionUpdated);

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	AStealth_ProjSingoloGameMode* GameMode = Cast<AStealth_ProjSingoloGameMode>(GameModeBase);
	GameMode->OnGameOver.AddUniqueDynamic(this, &AMyEnemyAIController::Handle_GameOver);

	RunBehaviorTree(BTEnemy);
}

void AMyEnemyAIController::Handle_GameOver(bool PlayerWon)
{
	AIPerceptionComponent->SetSenseEnabled(UAISense_Sight::StaticClass(), false);
	GetBlackboardComponent()->ClearValue("Player");
}

void AMyEnemyAIController::Handle_OnPerceptionUpdated(AActor* TargetActor, FAIStimulus Stimulus)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (TargetActor != Cast<AActor>(Player)) return;


	UBlackboardComponent* BlackBoard = GetBlackboardComponent();
	FName BlackBoardPlayerKey = "Player";
	FName BlackBoardStimulusLocationKey = "StimulusLocation";

	TSubclassOf<UAISense> StimulusClass = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus);

	if (StimulusClass == UAISense_Sight::StaticClass())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			Blackboard->SetValueAsObject(BlackBoardPlayerKey, Cast<UObject>(TargetActor));
			IsBeingSpotted = true;

			Blackboard->ClearValue(BlackBoardStimulusLocationKey);
		}
		else
		{
			Blackboard->SetValueAsVector(BlackBoardStimulusLocationKey, Stimulus.StimulusLocation);
			IsBeingSpotted = false;
		}
	}
	else if (StimulusClass == UAISense_Hearing::StaticClass())
	{
		if (IsBeingSpotted) return;

		if (Stimulus.WasSuccessfullySensed())
		{
			Blackboard->SetValueAsObject(BlackBoardPlayerKey, Cast<UObject>(TargetActor));

			Blackboard->SetValueAsVector(BlackBoardStimulusLocationKey, Stimulus.StimulusLocation);
		}
	}
}