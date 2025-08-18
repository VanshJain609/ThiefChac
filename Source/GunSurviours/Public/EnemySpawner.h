// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TimerHandle.h"
#include "Enemy.h"
#include "EnemySpawner.generated.h"

UCLASS()
class GUNSURVIOURS_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemy>EnemyActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime = 1.0f;

	FTimerHandle SpawnTimer;
	
	AEnemySpawner();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SpawnTimerTimeOut();
	void StartSpawning();
	void StopSpawning();
	void SpawnEnemy();

};
