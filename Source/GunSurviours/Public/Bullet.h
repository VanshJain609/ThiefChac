// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "Engine/TimerHandle.h"
#include "Bullet.generated.h"

UCLASS()
class GUNSURVIOURS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:
	//Adding Sphere Component for Bullet
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite)
	USphereComponent* SphereComp;

	//Adding Sprite for Bullet
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite)
	UPaperSpriteComponent* BulletSprite;

	UPROPERTY(BluePrintReadWrite)
	FVector2D MovementDirection;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float MovementSpeed = 300.0f;

	//To Check if the Bullet is Launched or Not
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsLaunched = false;

	//To Delete the Bullet After a Certain Time
	FTimerHandle DeleteTimer;
	

	
	ABullet();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Launch(FVector2D Direction, float Speed);
	void OnDeleteTimerTimeOut();

};
