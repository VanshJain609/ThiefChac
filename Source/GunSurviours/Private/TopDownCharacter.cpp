// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCharacter.h"

#include "Bullet.h"
#include "Kismet/KismetMathLibrary.h"


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

	//Setting up GunParent
	GunParent = CreateDefaultSubobject<USceneComponent>(TEXT("GunParent"));
	GunParent->SetupAttachment(RootComponent);

	//Setting up GunSprite
	GunSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("GunSprite"));
	GunSprite->SetupAttachment(GunParent);

	//Setting up BulletSpawnPosition
	BulletSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPosition"));
	BulletSpawnPosition->SetupAttachment(GunSprite);
}

void ATopDownCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Getting the PlayerController
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		//To Display Mouse Cursor Every Second
		PlayerController->SetShowMouseCursor(true);
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

bool ATopDownCharacter::IsInMapBoundsHorizontal(float XPos)
{
	// To Keep the Player Inside the Bounds
	bool Result = true;

	Result = (XPos > HorizontalLimits.X) && (XPos < HorizontalLimits.Y);
	return Result;
}

bool ATopDownCharacter::IsInMapBoundsVertical(float ZPos)
{
	bool Result = true;

	Result = (ZPos > VerticalLimits.X) && (ZPos < VerticalLimits.Y);
	return Result;
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
			FVector NewLocation = CurrentLocation + FVector(DistanceToMove.X, 0.0f, 0.0f);
			if (!IsInMapBoundsHorizontal(NewLocation.X))
			{
				NewLocation -= FVector(DistanceToMove.X, 0.0f, 0.0f);
			}
			NewLocation += FVector(0.0f, 0.0f, DistanceToMove.Y);
			if (!IsInMapBoundsVertical(NewLocation.Z))
			{
				NewLocation -= FVector(0.0f, 0.0f, DistanceToMove.Y);
			}
			SetActorLocation(NewLocation);
		}
	}

	//Rotate the Gun
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		//To Get the Location and Direction of the Mouse 
		FVector MouseWorldLocation , MouseWorldDirection;
		PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

		//Getting the Current Location and then giving the New Location
		FVector CurrentLocation = GetActorLocation();
		FVector Start = FVector(CurrentLocation.X, 0.0f, CurrentLocation.Z);
		FVector Target = FVector(MouseWorldLocation.X, 0.0f, MouseWorldLocation.Z);
		FRotator GunParentRotator = UKismetMathLibrary::FindLookAtRotation(Start, Target);

		GunParent->SetRelativeRotation(GunParentRotator);
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
		//Switching  Idle FLipbook Animation To Run Animation 
		CharacterFlipbook->SetFlipbook(RunFlipbook);

		// For Switching Player from Left to Right
		FVector FlipbookScale = CharacterFlipbook->GetComponentScale();
		if (MovementDirection.X < 0.0f)
		{
			if (FlipbookScale.X > 0.0f)
			{
				CharacterFlipbook->SetWorldScale3D(FVector(-1.0f, 1.0f, 1.0f));
			}
		}
		else if (MovementDirection.X > 0.0f)
		{
			if (FlipbookScale.X < 0.0f)
			{
				CharacterFlipbook->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
			}
		}
	}
}

void ATopDownCharacter::MoveCompleted(const FInputActionValue& Value)
{
	//Setting Movement Direction to 0
	MovementDirection = FVector2D(0.0f, 0.0f);

	//Switching Run Animation to Idle Animation
	CharacterFlipbook->SetFlipbook(IdleFlipbook);
}

void ATopDownCharacter::Shoot(const FInputActionValue& Value)
{
	if (CanShoot)
	{
		CanShoot = false;
		//Spawn Bullet Actors
		ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletActorToSpawn, BulletSpawnPosition->
			GetComponentLocation(), FRotator(0.0f, 0.0f, 0.0f));
		check(Bullet);

		//Get Mouse World Location
		APlayerController* PlayerController = Cast<APlayerController>(Controller);
		check(PlayerController);
			FVector MouseWorldLocation, MouseWorldDirection;
			PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

		//Calculate Bullet Direction
		FVector CurrentLocation = GetActorLocation();
		FVector2D BulletDirection = FVector2D(MouseWorldLocation.X - CurrentLocation.X, MouseWorldLocation.Z - CurrentLocation.Z);
		BulletDirection.Normalize();

		//Launch the Bullet
		float BulletSpeed = 300.0f;
		Bullet->Launch(BulletDirection, BulletSpeed);
		
		GetWorldTimerManager().SetTimer(ShootCoolDownTimer, this, &ATopDownCharacter::OnShootCoolDownTimerTimeOut, 1.0f, false, ShootCoolDownDurationInSeconds);
	}
}

void ATopDownCharacter::OnShootCoolDownTimerTimeOut()
{
	CanShoot = true;
}