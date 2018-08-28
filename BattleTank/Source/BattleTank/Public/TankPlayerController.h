// Copyright Red Wagon

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 Responsible for helping player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	// where aim at occurs - calls supporting functions below
	virtual void Tick(float) override;

protected:

	virtual void BeginPlay() override;

	// don't actually have to implement due to the macro
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:

	// start the tank barrel moving towards crosshair so 
	// shot hits where crosshair intersects world
	void AimTowardsCrosshair();


	// check if crosshair over landscape, and return true 
	// if yes, false if no. Also set location in the out parameter fvector
	bool GetSightRayHitLocation(FVector &) const;

	// when tank possessed this called
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();
};
