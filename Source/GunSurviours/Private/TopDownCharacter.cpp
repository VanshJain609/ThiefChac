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

	//Adding Movement to the Player
	if (CanMove)
	{
		//Checking if the Key is Pressed or Not
		if (MovementDirection.Length() > 0.0f)
		{
			// If Movement Length is Greater than 1 then Normalize the Vector by Normalize Function
			if (MovementDirection.Length() > 1.0f)
			{
				MovementDirection.Normalize();
			}
			//Calculating the Distance to Move
			FVector2D DistanceToMove = MovementDirection * MovementSpeed * DeltaTime;
			
			//Getting the Current Location
			FVector CurrentLocation = GetActorLocation();

			//Getting the New Location
			FVector NewLocation = CurrentLocation + FVector(DistanceToMove.X, 0.0f, DistanceToMove.Y);
			SetActorLocation(NewLocation);
		}
	}

}

void ATopDownCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Casting PlayerInputComponent to EnhancedInputComponent
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		//Binding Actions
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATopDownCharacter::MoveTriggered);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed,this, &ATopDownCharacter::MoveCompleted);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &ATopDownCharacter::MoveCompleted);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ATopDownCharacter::Shoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ATopDownCharacter::Shoot);
	}
}

void ATopDownCharacter::MoveTriggered(const FInputActionValue& Value)
{
	//Calling Actual Vector from FInputActionValue
	FVector2D MoveActionValue = Value.Get<FVector2D>();

	//Setting MoveDirection Value to MoveActionValue
	if (CanMove)
	{
		MovementDirection = MoveActionValue;
	}
}

void ATopDownCharacter::MoveCompleted(const FInputActionValue& Value)
{
	//Setting Movement Direction to 0
	MovementDirection = FVector2D(0.0f, 0.0f);
}

void ATopDownCharacter::Shoot(const FInputActionValue& Value)
{
}