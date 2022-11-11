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
#include "Runtime/Engine/Public/TimerManager.h"
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

	// Setters.
	void SetRotation(FRotator value);
	void SetPlayerState(int value);

	// Getters.
	FRotator GetRotation();
	FVector GetLocation();
	FVector GetForward();

	// Player controls.
	void HoriMove(float value);
	void VertMove(float value);
	void HoriRot(float value);
	void RollRot();
	void VertRot(float value);
	void Fly(float value);
	void Gravitate(FVector value);
	void JetPack(float value);

	// Player variables.
	int playerState;
	bool rollKey;

private:
	// Create the capsule component.
	UPROPERTY(EditAnywhere, Category = "Collision")
		UCapsuleComponent* CapsuleComponent;

	// Create the camera component.
	UPROPERTY(EditAnywhere, Category = "Camera")
		UCameraComponent* cam;
};