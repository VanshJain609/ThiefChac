// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "Bullet.generated.h"

UCLASS()
class GUNSURVIOURS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite)
	UPaperSpriteComponent* BulletSprite;

	
	ABullet();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
