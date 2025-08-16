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


	//Constructor
	ATopDownCharacter();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
