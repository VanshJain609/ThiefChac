// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SetRootComponent(SphereComp);

	BulletSprite = CreateDefaultSubobject<UPaperSpriteComponent>("BulletSprite");
	BulletSprite->SetupAttachment(RootComponent);

}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

