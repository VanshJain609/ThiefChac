// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "Kismet/GameplayStatics.h"

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
		ScoreChangeDelegate.Broadcast(Score);
	}
}

void AMyGameMode::AddScore(int AmountToAdd)
{
	int NewScore = Score + AmountToAdd;
	SetScore(NewScore);
}

void AMyGameMode::RestartGame()
{
	GetWorldTimerManager().SetTimer(RestartGameTimer, this , &AMyGameMode::RestartGameTimerTimeOut, 1.0f, false, TimeBeforeRestart);
}

void AMyGameMode::RestartGameTimerTimeOut()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainLevel"));
}
