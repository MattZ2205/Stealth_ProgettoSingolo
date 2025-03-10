// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPatrolPoint.h"

AMyPatrolPoint::AMyPatrolPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(MeshComponent);
}

void AMyPatrolPoint::BeginPlay()
{
	Super::BeginPlay();

}

void AMyPatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

