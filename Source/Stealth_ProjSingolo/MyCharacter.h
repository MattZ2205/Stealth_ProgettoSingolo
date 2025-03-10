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

UCLASS()
class STEALTH_PROJSINGOLO_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

private:
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

protected:
	virtual void BeginPlay() override;
	void MovePlayer(const FInputActionValue& Value);
	void MovePlayerCamera(const FInputActionValue& Value);
	void PlayerCrouch(const FInputActionValue& Value);

public:
	AMyCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Attack(APawn* Entity);

	UFUNCTION()
	void ReceiveAttack();
};
