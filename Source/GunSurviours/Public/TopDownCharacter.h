// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
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

	//Creating Scene Component for Gun
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* GunParent;

	//Creating Sprite for Gun
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* GunSprite;

	//Creating Scene Component for Bullet Spawn
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* BulletSpawnPosition;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperFlipbook* RunFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D HorizontalLimits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D VerticalLimits;

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

	//To Chcek if Player is Inside the BoundWalls or Not
	bool IsInMapBoundsHorizontal(float XPos);
	bool IsInMapBoundsVertical(float ZPos);

};
