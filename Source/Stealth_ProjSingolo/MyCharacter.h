// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE(FOnPlayerDeath);

UCLASS()
class STEALTH_PROJSINGOLO_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FOnPlayerDeath OnPlayerDeath;

protected:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere)
	UInputAction* Move;

	UPROPERTY(EditAnywhere)
	UInputAction* MoveCamera;

	UPROPERTY(EditAnywhere)
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere)
	UInputAction* AttackAction;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* AttackCheckLocation;

	UPROPERTY(EditDefaultsOnly)
	float AttackCheckLenght = 10;

	UPROPERTY(EditAnywhere)
	bool IsAttacking;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MovePlayer(const FInputActionValue& Value);
	void MovePlayerCamera(const FInputActionValue& Value);
	void PlayerCrouch(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Attack(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected))
	void GetBehindEnemyTransform(FTransform& BehindTransform, AMyEnemyReal* Enemy);
public:
	AMyCharacter();

	UFUNCTION()
	void ReceiveAttack();
};
