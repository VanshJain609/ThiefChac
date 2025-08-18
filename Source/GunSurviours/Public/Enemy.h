// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "TopDownCharacter.h"
#include "Enemy.generated.h"

UCLASS()
class GUNSURVIOURS_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* EnemyFlipbook;

	//Creating Refrence for the Enemy so that Enemy can Chase the Player
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ATopDownCharacter* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsAlive = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanFollow = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StopDistance = 20.0f;
	
	AEnemy();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
