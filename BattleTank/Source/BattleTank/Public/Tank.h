// Copyright Red Wagon

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// where to aim at
	void AimAt(FVector HitLocation);

	// called from blueprints to fire
	UFUNCTION(BlueprintCallable, Category = Actions)
	void Fire();

protected:
	// for aiming the barrel and moving turret
	UPROPERTY(BlueprintReadOnly, Category = Input)
	UTankAimingComponent* TankAimingComponent = nullptr;

	// for fly by wire control
	UPROPERTY(BlueprintReadOnly, Category=Input)
	UTankMovementComponent* TankMovingComponent = nullptr;

private:
	// just allow this change in blueprint, ie default base, not instances
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBP;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000; // 1000 m/s
	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	// Local reference for projectile
	UTankBarrel* Barrel = nullptr;

	// last time fired in seconds
	double LastFireTime = 0;
};
