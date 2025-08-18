// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	StartSpawning();
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEnemySpawner::StartSpawning()
{
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawner::SpawnTimerTimeOut, SpawnTime, true, SpawnTime);
}

void AEnemySpawner::StopSpawning()
{
	GetWorldTimerManager().ClearTimer(SpawnTimer);
}

void AEnemySpawner::SpawnTimerTimeOut()
{
	SpawnEnemy();
}

void AEnemySpawner::SpawnEnemy()
{
	FVector EnemyLocation = GetActorLocation();
	AEnemy* Enemy = GetWorld()->SpawnActor<AEnemy>(EnemyActorToSpawn, EnemyLocation, FRotator::ZeroRotator);
}

