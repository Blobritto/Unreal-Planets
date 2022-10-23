// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Math/Rotator.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Math/TransformNonVectorized.h"
#include "MyFPCharacter.generated.h"

UCLASS()
class PRAPI3_API AMyFPCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyFPCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void SetRotation(FRotator value);
	FRotator GetRotation();
	FVector GetLocation();
	FVector GetForward();
	void Gravitate(FVector value);
	UCapsuleComponent* MeshRootComp;


	void HoriMove(float value);
	void VertMove(float value);

	void HoriRot(float value);
	void VertRot(float value);

	void Jump();


private:



	UPROPERTY(EditAnywhere, Category = "Collision")
		UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
		UCameraComponent* cam;


};