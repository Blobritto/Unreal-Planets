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

	playerState = 1;
	rollKey = false;

	//MeshRootComp = Cast<UCapsuleComponent>(GetRootComponent());
}

// Called when the game starts or when spawned
void AMyFPCharacter::BeginPlay()
{
	Super::BeginPlay();

	//shipWidgetInstance = Cast<UUserWidget>(CreateWidget(GetWorld(), ShipWidget));
	//cam->shipWidgetInstance->AddToViewport();


}

// Called every frame
void AMyFPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//rollKey = false;
}

// Called to bind functionality to input
void AMyFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Hori", this, &AMyFPCharacter::HoriMove);
	InputComponent->BindAxis("Vert", this, &AMyFPCharacter::VertMove);

	InputComponent->BindAxis("HoriRot", this, &AMyFPCharacter::HoriRot);
	InputComponent->BindAxis("VertRot", this, &AMyFPCharacter::VertRot);

	InputComponent->BindAxis("Fly", this, &AMyFPCharacter::Fly);

	InputComponent->BindAction("RollRot",IE_Pressed, this, &AMyFPCharacter::RollRot);

	//InputComponent->BindAction("Jump", IE_Pressed, this, &AMyFPCharacter::Jump);
	//InputComponent->BindAction("Launch", IE_Pressed, this, &AMyFPCharacter::Launch);
	InputComponent->BindAxis("JetPack", this, &AMyFPCharacter::JetPack);
}


void AMyFPCharacter::HoriMove(float value)
{
	if (value)
	{
		if (playerState == 1)
		{
			value *= 5;
		}
		CapsuleComponent->UPrimitiveComponent::AddForce(CapsuleComponent->USceneComponent::GetRightVector() * 700000 * value);
	}
}


void AMyFPCharacter::VertMove(float value)
{
	if (value)
	{
		if (playerState == 1)
		{
			value *= 5;
		}
		CapsuleComponent->UPrimitiveComponent::AddForce(CapsuleComponent->USceneComponent::GetForwardVector() * 450000 * value);
	}
}


void AMyFPCharacter::HoriRot(float value)
{
	if (value)
	{
		if (playerState == 1)
		{
			if (rollKey == true)
			{
				FRotator rotat = UKismetMathLibrary::MakeRotator(value, 0, 0);
				AddActorLocalRotation(rotat);
			}
			else
			{
				FRotator rotat1 = UKismetMathLibrary::MakeRotator(0, 0, value);
				AddActorLocalRotation(rotat1);
			}
		}
		else if (playerState == 2)
		{
			FRotator rotat2 = UKismetMathLibrary::MakeRotator(0, 0, value);
			AddActorLocalRotation(rotat2);
		}
	}
}


void AMyFPCharacter::RollRot()
{
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


void AMyFPCharacter::VertRot(float value)
{
	if (value)
	{
		if (playerState == 1)
		{
			FRotator rotat;
			rotat = UKismetMathLibrary::MakeRotator(0, value, 0);
			AddActorLocalRotation(rotat);
		}
		else
		{
			float temp = cam->GetRelativeRotation().Pitch + value;

			if (temp < 80 && temp > -80)
			{
				cam->AddLocalRotation(FRotator(value, 0, 0));
			}
		}
	}
}

/*
void AMyFPCharacter::Jump()
{
	if (playerState == 1)
	{
	}
	else
	{
		CapsuleComponent->UPrimitiveComponent::AddImpulse(GetActorUpVector() * 200000);
	}
}
*/

void AMyFPCharacter::Fly(float value)
{
	if (value)
	{
		if (playerState == 1)
		{
			CapsuleComponent->UPrimitiveComponent::AddForce(CapsuleComponent->USceneComponent::GetUpVector() * 7000000 * value);
		}
	}
}




/*
void AMyFPCharacter::Launch()
{
	if (playerState == 1)
	{
		CapsuleComponent->UPrimitiveComponent::AddForce(CapsuleComponent->USceneComponent::GetForwardVector() * 800000000);
	}

		
	//FTimerDelegate TimerDelegate;
	//TimerDelegate.BindLambda([&]
	//	{
	//		playerState = 1;
	//		//rollKey = false;
	//		FRotator camRot = cam->USceneComponent::GetComponentRotation();
	//		FRotator realCamRot = FRotator(camRot.Pitch, 0, 0);
	//		cam->USceneComponent::SetRelativeRotation(FRotator(0, 0, 0));
	//		AActor::SetActorRotation(camRot);
	//	});
	//
	//FTimerHandle TimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.2f, false);
}
*/


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


void AMyFPCharacter::SetPlayerState(int value)
{
	playerState = value;

	if (value == 1)
	{
		//rollKey = false;
		FRotator camRot = cam->USceneComponent::GetComponentRotation();
		FRotator realCamRot = FRotator(camRot.Pitch, 0, 0);
		cam->USceneComponent::SetRelativeRotation(FRotator(0, 0, 0));
		AActor::SetActorRotation(camRot);
	}
}

void AMyFPCharacter::JetPack(float value)
{
	if (value && playerState == 2)
	{
		CapsuleComponent->UPrimitiveComponent::AddForce(CapsuleComponent->USceneComponent::GetUpVector() * value * 1000000);
	}
}