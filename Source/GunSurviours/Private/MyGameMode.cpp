// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

AMyGameMode::AMyGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	SetScore(0);
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetScore(0);
}

void AMyGameMode::SetScore(int NewScore)
{
	if (NewScore >= 0)
	{
		Score = NewScore;
	}
}

void AMyGameMode::AddScore(int AmountToAdd)
{
	int NewScore = Score + AmountToAdd;
	SetScore(NewScore);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Score: %d"), Score));
}
