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

}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(player->GetLocation(), GetActorLocation());

	FRotator rotz = UKismetMathLibrary::MakeRotFromZX(UKismetMathLibrary::GetForwardVector(rot), player->GetForward());




	rotz.Add(0, 0, 180);


	player->SetRotation(rotz);




	player->Gravitate(UKismetMathLibrary::GetForwardVector(rot));

}


