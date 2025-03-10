// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIBehaviorComponent.h"

UMyAIBehaviorComponent::UMyAIBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMyAIBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UMyAIBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMyAIBehaviorComponent::UpdateToNextPatrolPoint(AMyPatrolPoint*& CurrentPatrolPoint) const
{
	if (!CurrentPatrolPoint) return;

	int index = PatrolPath.Find(CurrentPatrolPoint);

	if (PatrolPath.Num() <= index + 1)
	{
		index = 0;
	}
	else
	{
		index += 1;
	}

	CurrentPatrolPoint = PatrolPath[index];
}