#include "MyFPCharacter.h"

// Sets default values
AMyFPCharacter::AMyFPCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Creates the capsule mesh component and sets it as the root component for the actor. This is what collides with the world and has the forces applied to.
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComponent;

	// Creates the camera component and attaches it to the root component, here being the capsule mesh.
	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cam->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	// The location of the camera is moved up slightly to give a better player height, so the camera is not constantly on the floor.
	cam->SetWorldLocation(FVector(0, 0, 40));

	// Sets the playerstate to be 1 by default so space controls are useable.
	// Sets the rollkey to be false, as this is not the standard rotation axis for a player camera.
	playerState = 1;
	rollKey = false;
}

// Called when the game starts or when spawned
void AMyFPCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyFPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Binds movement of the player.
	InputComponent->BindAxis("Hori", this, &AMyFPCharacter::HoriMove);
	InputComponent->BindAxis("Vert", this, &AMyFPCharacter::VertMove);
	InputComponent->BindAxis("Fly", this, &AMyFPCharacter::Fly);
	InputComponent->BindAxis("JetPack", this, &AMyFPCharacter::JetPack);

	// Binds rotation of the player and the player's camera component.
	InputComponent->BindAxis("HoriRot", this, &AMyFPCharacter::HoriRot);
	InputComponent->BindAxis("VertRot", this, &AMyFPCharacter::VertRot);

	// Toggles the roll rotation while in space.
	InputComponent->BindAction("RollRot", IE_Pressed, this, &AMyFPCharacter::RollRot);
}

// Adds a force to the player pawn to create left and right player movement.
void AMyFPCharacter::HoriMove(float value)
{
	// Only calls the rest of the function if a value is registered, simply for optimisation.
	if (value)
	{
		if (playerState == 1)
		{
			// If the player is floating through space, make them move 5 times faster than normal, simply to make space travel shorter and less tedious.
			value *= 5;
		}
		CapsuleComponent->UPrimitiveComponent::AddForce(CapsuleComponent->USceneComponent::GetRightVector() * 700000 * value);
	}
}

// Adds a force to the player pawn to create forward and backward player movement.
void AMyFPCharacter::VertMove(float value)
{
	// Only calls the rest of the function if a value is registered, simply for optimisation.
	if (value)
	{
		if (playerState == 1)
		{
			// If the player is floating through space, make them move 5 times faster than normal, simply to make space travel shorter and less tedious.
			value *= 5;
		}
		CapsuleComponent->UPrimitiveComponent::AddForce(CapsuleComponent->USceneComponent::GetForwardVector() * 700000 * value);
	}
}

// Rotates the player / camera based on the X axis of the mouse.
void AMyFPCharacter::HoriRot(float value)
{
	// Only calls the rest of the function if a value is registered, simply for optimisation.
	if (value)
	{
		if (playerState == 1 && rollKey == true)
		{
			// If the roll key is toggled on, and the player is in space, the X axis of the player rotates, rather than the Z, to give 6 degrees of freedom of movement.
			AddActorLocalRotation(UKismetMathLibrary::MakeRotator(value, 0, 0));
		}
		else
		{	
			// If these conditions are not both met, the player rotates on the Z axis as is standard for player controllers.
			AddActorLocalRotation(UKismetMathLibrary::MakeRotator(0, 0, value));
		}
	}
}

// Rotates the player / camera based on the Y axis of the mouse.
void AMyFPCharacter::VertRot(float value)
{
	// Only calls the rest of the function if a value is registered, simply for optimisation.
	if (value)
	{
		if (playerState == 1)
		{
			// Turns the value from the input into a rotator and adds it to the player local rotation.
			AddActorLocalRotation(UKismetMathLibrary::MakeRotator(0, value, 0));
		}
		else
		{
			// Sets bounds for the furthest up and down the player can look.
			float temp = cam->GetRelativeRotation().Pitch + value;
			if (temp < 80 && temp > -80)
			{
				cam->AddLocalRotation(FRotator(value, 0, 0));
			}
		}
	}
}

// A flip switch to toggle between normal rotation and roll rotation.
void AMyFPCharacter::RollRot()
{
	// If in one state, change to the other.
	// But only when the player is in space.
	if (playerState == 1)
	{
		if (rollKey == true)
		{
			rollKey = false;
		}
		else
		{
			rollKey = true;
		}
	}
}

// Give the player vertical movement when in space for a smoother travel experience.
void AMyFPCharacter::Fly(float value)
{
	// Only calls the rest of the function if a value is registered, simply for optimisation.
	if (value)
	{
		if (playerState == 1)
		{
			CapsuleComponent->UPrimitiveComponent::AddForce(CapsuleComponent->USceneComponent::GetUpVector() * 7000000 * value);
		}
	}
}

// Gets the rotation off the actor.
FRotator AMyFPCharacter::GetRotation()
{
	FRotator rotation = AActor::GetActorRotation();
	return rotation;
}

// Sets the rotation of the actor.
void AMyFPCharacter::SetRotation(FRotator value)
{
	AActor::SetActorRotation(value);
}

// Gets the location of the actor.
FVector AMyFPCharacter::GetLocation()
{
	FVector location = AActor::GetActorLocation();
	return location;
}

// Gets the forward vector of the actor.
FVector AMyFPCharacter::GetForward()
{
	FVector forward = GetActorForwardVector();
	return forward;
}

// Adds a force to the player, primarily in a downward direction.
void AMyFPCharacter::Gravitate(FVector value)
{
	CapsuleComponent->UPrimitiveComponent::AddForce(value * 50000);
}

// Sets the playerstate of the player.
void AMyFPCharacter::SetPlayerState(int value)
{
	playerState = value;

	if (value == 1)
	{
		// If switching from on planet to space, the player is reoriented so that the camera is locally 0, 0, 0 to the actor.
		// If I don't do this, the rotation of the player in space is all wrong, as the camera is stuck facing in the wrong direction.
		// In space, vertical rotation is the whole actor rather than the camera component.
		FRotator camRot = cam->USceneComponent::GetComponentRotation();
		FRotator realCamRot = FRotator(camRot.Pitch, 0, 0);
		cam->USceneComponent::SetRelativeRotation(FRotator(0, 0, 0));
		AActor::SetActorRotation(camRot);
	}
}

// Gives the player a vertical boost when on a planet.
void AMyFPCharacter::JetPack(float value)
{
	// Only calls the rest of the function if a value is registered, simply for optimisation.
	if (value && playerState == 2)
	{
		CapsuleComponent->UPrimitiveComponent::AddForce(CapsuleComponent->USceneComponent::GetUpVector() * value * 1000000);
	}
}