#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFPCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Math/Rotator.h"
#include "Math/TransformNonVectorized.h"
#include "GameFramework/Actor.h"
#include "Planet.generated.h"

UCLASS()
class PRAPI3_API APlanet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlanet();

	// References for the player in the planet script.
	AActor* playerActor;
	AMyFPCharacter* player;
	
	// Planet variables
	float scale;
	float gravityMultiplier;
	float distanceToPlayer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Create the sphere component.
	UPROPERTY(EditAnywhere, Category = "Sphere")
		USphereComponent* sphere;
};
