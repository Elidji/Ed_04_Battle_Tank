// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 Tank Barrel is used to move barrel
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward movement and +1 is max upward movement
	void Elevate(float RelativeSpeed);

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegreesPerSecond = 10;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxElevation = 35;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MinElevation = 0;
};
