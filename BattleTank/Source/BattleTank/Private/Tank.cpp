// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Tank.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/Projectile.h"
#include "../Public/TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;  // doesn't tick
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }

	bool bIsReloaded = (FPlatformTime::Seconds()-LastFireTime) >= ReloadTimeInSeconds;
	// if time passed for reload, fire
	if (bIsReloaded)
	{
		// Spawn a projectile at end barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}
