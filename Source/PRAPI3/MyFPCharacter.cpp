// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFPCharacter.h"

// Sets default values
AMyFPCharacter::AMyFPCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//bUseControllerRotationYaw = false;
	//uint32 bUsePawnControlRotation = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	//CapsuleComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	RootComponent = CapsuleComponent;


	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cam->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	cam->SetWorldLocation(FVector(0, 0, 40));

	//MeshRootComp = Cast<UCapsuleComponent>(GetRootComponent());
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

	InputComponent->BindAxis("Hori", this, &AMyFPCharacter::HoriMove);
	InputComponent->BindAxis("Vert", this, &AMyFPCharacter::VertMove);

	InputComponent->BindAxis("HoriRot", this, &AMyFPCharacter::HoriRot);
	InputComponent->BindAxis("VertRot", this, &AMyFPCharacter::VertRot);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyFPCharacter::Jump);
}


void AMyFPCharacter::HoriMove(float value)
{
	if (value)
	{
		CapsuleComponent->UPrimitiveComponent::AddForce(CapsuleComponent->USceneComponent::GetRightVector() * 50000 * value);
	}
}


void AMyFPCharacter::VertMove(float value)
{
	if (value)
	{
		CapsuleComponent->UPrimitiveComponent::AddForce(CapsuleComponent->USceneComponent::GetForwardVector() * 50000 * value);
	}
}


void AMyFPCharacter::HoriRot(float value)
{
	if (value)
	{
		FRotator rotat = UKismetMathLibrary::MakeRotator(0, 0, value);
		AddActorLocalRotation(rotat);
	}
}


void AMyFPCharacter::VertRot(float value)
{
	if (value)
	{
		float temp = cam->GetRelativeRotation().Pitch + value;

		if (temp < 80 && temp > -80)
		{
			cam->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}


void AMyFPCharacter::Jump()
{
	CapsuleComponent->UPrimitiveComponent::SetPhysicsLinearVelocity(GetActorUpVector() * 500);
}


FRotator AMyFPCharacter::GetRotation()
{
	FRotator rotation = AActor::GetActorRotation();

	return rotation;
}

void AMyFPCharacter::SetRotation(FRotator value)
{
	AActor::SetActorRotation(value);
}

FVector AMyFPCharacter::GetLocation()
{
	FVector location = AActor::GetActorLocation();

	return location;
}

FVector AMyFPCharacter::GetForward()
{
	FVector forward = GetActorForwardVector();

	return forward;
}


void AMyFPCharacter::Gravitate(FVector value)
{
	CapsuleComponent->UPrimitiveComponent::AddForce(value * 50000);
}

