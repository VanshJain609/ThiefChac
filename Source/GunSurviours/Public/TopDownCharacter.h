// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "InputAction.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "TopDownCharacter.generated.h"

UCLASS()
class GUNSURVIOURS_API ATopDownCharacter : public APawn
{
	GENERATED_BODY()

public:
	//Create CapsuleComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	//Create Flipbook
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* CharacterFlipbook;

	// Creating MappingContext
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* InputMappingContext;

	//Creating MoveAction
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UInputAction* MoveAction;

	//Creating ShootAction
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UInputAction* ShootAction;

	// Creating Flipbook for Animations
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperFlipbook* IdleFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* RunFlipbook;

	//MovementSpeed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 100.f;

	//MovementDirection
	UPROPERTY(BlueprintReadWrite)
	FVector2D MovementDirection;

	// Creating Bool to Check Player can Move or Not
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanMove = true;
	
	//Constructor
	ATopDownCharacter();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Defining Input Actions Functions
	void MoveTriggered(const FInputActionValue& Value);
	void MoveCompleted(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);

};
