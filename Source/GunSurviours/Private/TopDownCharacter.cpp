// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCharacter.h"


ATopDownCharacter::ATopDownCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Setting up CapsuleComponent
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	//Attaching Capsule Component as RootComponent
	SetRootComponent(CapsuleComp);

	//Setting up FlipbookComponent
	CharacterFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("CharacterFlipbook"));
	//Attaching CharacterFlipbook to the RootComponent
	CharacterFlipbook->SetupAttachment(RootComponent);

}

void ATopDownCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Getting the PlayerController
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		//Getting Enhanced SubSystems from the Player Controller
		UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
		(PlayerController->GetLocalPlayer());
		if (SubSystem)
		{
			//Registering the MappingContext
			SubSystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ATopDownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATopDownCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

