// Fill out your copyright notice in the Description page of Project Settings.

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

	// called from blueprints, passes the barrel
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	// called from blueprints, passes the turret
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);

	// called from blueprints to fire
	UFUNCTION(BlueprintCallable, Category = Actions)
		void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// components added to blueprints when this class is created - in constructor
	
	// for aiming the barrel and moving turret
	UTankAimingComponent* TankAimingComponent = nullptr;

	// for fly by wire control
	UPROPERTY(BlueprintReadOnly, Category=Input)
	UTankMovementComponent* TankMovingComponent = nullptr;

private:
	// just allow this change in blueprint, ie default base, not instances
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBP;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 4000; // 1000 m/s
	UPROPERTY(EditAnywhere, Category = Firing)
		float ReloadTimeInSeconds = 3;

	// Local reference for projectile
	UTankBarrel* Barrel = nullptr;

	// last time fired in seconds
	double LastFireTime = 0;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
