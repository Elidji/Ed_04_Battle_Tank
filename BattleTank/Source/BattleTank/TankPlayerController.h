// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	// where aim at occurs - calls supporting functions below
	virtual void Tick(float) override;

	ATank * GetControlledTank() const;

protected:

	virtual void BeginPlay() override;

private:

	// start the tank barrel moving towards crosshair so 
	// shot hits where crosshair intersects world
	void AimTowardsCrosshair();


	// check if crosshair over landscape, and return true 
	// if yes, false if no. Also set location in the out parameter fvector
	bool GetSightRayHitLocation(FVector &) const;
};
