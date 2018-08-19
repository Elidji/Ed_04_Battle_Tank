// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Tank.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/TankMovementComponent.h"
#include "../Public/Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;  // doesn't tick

	// No need to protect since created at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	TankMovingComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

// called from blueprint
void ATank::SetBarrelReference(UTankBarrel *BarrelToSet)
{
	if (!BarrelToSet) { return; }
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

// called from blueprint
void ATank::SetTurretReference(UTankTurret *TurretToSet)
{
	if (!TurretToSet) { return; }
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds()-LastFireTime) >= ReloadTimeInSeconds;
	// if time passed for reload, fire
	if (Barrel && bIsReloaded)
	{
		// Spawn a projectile at end barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}
