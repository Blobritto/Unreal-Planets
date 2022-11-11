#include "Planet.h"

// Sets default values
APlanet::APlanet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the sphere and attach it to the root component.
	sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	sphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();

	// Have reference to the player inside of the planet script, so functions can be called and maths can be calculated.
	TSubclassOf<AMyFPCharacter> classToFind;
	classToFind = AMyFPCharacter::StaticClass();
	playerActor = UGameplayStatics::GetActorOfClass(GetWorld(), classToFind);
	player = Cast<AMyFPCharacter>(playerActor);

	// Sets the planet at arandom size, and calculates the relative gravity intensity.
	scale = FMath::RandRange(400, 1500);
	AActor::SetActorScale3D(FVector(scale, scale, scale));
	gravityMultiplier = (FMath::Sqrt(scale) / 15);

	// The planet is moved to a random location and rotation in the map.
	sphere->USceneComponent::SetWorldLocation(FVector(FMath::RandRange(-1000000, 1000000), FMath::RandRange(-1000000, 1000000), FMath::RandRange(-1000000, 1000000)));
	sphere->USceneComponent::SetWorldRotation(FRotator(FMath::RandRange(0, 360), FMath::RandRange(0, 360), FMath::RandRange(0, 360)));
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Calculates the distance between the player and each planet.
	distanceToPlayer = AActor::GetDistanceTo(player);
	
	// Rotates the planet to simulate planetary revolution.
	sphere->AddLocalRotation(FRotator(0, 0.04f, 0));

	if (distanceToPlayer < (scale * 200))
	{
		// Gets the rotation needed for the player to have the planet under their feet.
		FRotator rot = UKismetMathLibrary::FindLookAtRotation(player->GetLocation(), GetActorLocation());
		FRotator rotz = UKismetMathLibrary::MakeRotFromZX(UKismetMathLibrary::GetForwardVector(rot), player->GetForward());
		rotz.Add(0, 0, 180);
		FVector GravityScale = (UKismetMathLibrary::GetForwardVector(rot) * (scale/100));

		if (distanceToPlayer > (scale * 100))
		{
			// When near the planet, but not too near, the player floats towards it at half gravity while maintaining space movment inputs.
			// This is also the range where the player state is forced to 1, as when leaving a pplanet, the player must pass through this area.
			player->Gravitate(GravityScale * 0.5);
			player->SetPlayerState(1);
		}
		else
		{
			// The player is rotated the the planet is under them, they are gravitated towards the planet, the rollkey is forced to false so rotation is normal, and the playerstate is set to 2 for the correct movement controls.
			player->SetRotation(FMath::RInterpTo(player->GetRotation(), rotz, DeltaTime, 2));
			player->Gravitate(GravityScale);
			player->rollKey = false;
			player->SetPlayerState(2);
		}
	}
}