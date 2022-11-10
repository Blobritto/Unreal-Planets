// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"

// Sets default values
APlanet::APlanet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	sphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<AMyFPCharacter> classToFind;
	classToFind = AMyFPCharacter::StaticClass();
	playerActor = UGameplayStatics::GetActorOfClass(GetWorld(), classToFind);
	player = Cast<AMyFPCharacter>(playerActor);

	scale = FMath::RandRange(400, 1500);
	AActor::SetActorScale3D(FVector(scale, scale, scale));
	gravityMultiplier = (FMath::Sqrt(scale) / 15);
	int newLocationX = FMath::RandRange(-1000000, 1000000);
	int newLocationY = FMath::RandRange(-1000000, 1000000);
	int newLocationZ = FMath::RandRange(-1000000, 1000000);

	int newRotationX = FMath::RandRange(0, 360);
	int newRotationY = FMath::RandRange(0, 360);
	int newRotationZ = FMath::RandRange(0, 360);

	FVector newLocation = FVector(newLocationX, newLocationY, newLocationZ);
	FRotator newRotation = FRotator(newRotationX, newRotationY, newRotationZ);

	sphere->USceneComponent::SetWorldLocation(newLocation);
	sphere->USceneComponent::SetWorldRotation(newRotation);

}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	distanceToPlayer = AActor::GetDistanceTo(player);
	sphere->AddLocalRotation(FRotator(0, 0.04f, 0));

	if (distanceToPlayer < (scale * 200))
	{
		FRotator rot = UKismetMathLibrary::FindLookAtRotation(player->GetLocation(), GetActorLocation());
		FRotator rotz = UKismetMathLibrary::MakeRotFromZX(UKismetMathLibrary::GetForwardVector(rot), player->GetForward());
		rotz.Add(0, 0, 180);
		FVector GravityScale = (UKismetMathLibrary::GetForwardVector(rot) * (scale/100));


		if (distanceToPlayer > (scale * 100))
		{
			player->Gravitate(GravityScale * 0.5);
			player->SetPlayerState(1);
		}

		else
		{
			player->SetRotation(FMath::RInterpTo(player->GetRotation(), rotz, DeltaTime, 2));
			player->Gravitate(GravityScale);
			player->rollKey = false;
			player->SetPlayerState(2);
		}

	}
	else
	{
		//player->SetPlayerState(1);
	}

}




///UPTODATECHECK


