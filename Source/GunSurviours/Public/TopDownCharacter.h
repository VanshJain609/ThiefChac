// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TopDownCharacter.generated.h"

UCLASS()
class GUNSURVIOURS_API ATopDownCharacter : public APawn
{
	GENERATED_BODY()

public:
	ATopDownCharacter();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
