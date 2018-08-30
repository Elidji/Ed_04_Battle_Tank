// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "../Public/Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// so first firing is after reload, prevents firing right away on game launch
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	// if reloading 
	if (AmmoAmount <= 0)
	{
		FiringStatus = EFiringStatus::NoAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) 
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	// if barrel moving
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	// not moving or reloading
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}

}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

int32 UTankAimingComponent::GetAmmoAmt() const
{
	return AmmoAmount;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	// make sure we have a barrel and turret
	if (!ensure(Barrel || Turret)) { return; }

	// grab the socket location from the barrel, placed at end of barrel in unreal
	auto BarrelLocation = Barrel->GetSocketLocation(FName("Projectile"));
	// our direction to fire
	FVector LaunchVelocity;
	TArray<AActor*> ActorList;
	// must include these parameters, otherwise will break -- bug in code. Issue is it shows everything after launch speed as 
	// optional, but that will break it. 
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,            // just a reference to our tank aim component
		LaunchVelocity,  // pass by reference to get aim direction
		BarrelLocation,  // start
		HitLocation,     // end
		LaunchSpeed,     // speed
		false,			 // don't use high arc
		0,               // no collision radius
		0,               // no gravity
		ESuggestProjVelocityTraceOption::DoNotTrace   // don't trace along path for interfering objects
	);

	if (bHaveAimSolution)
	{
		// unit vector representation 
		AimDirection = LaunchVelocity.GetSafeNormal();
		// move the barrel
		MoveBarrel();
	}
}

void UTankAimingComponent::MoveBarrel()
{
	// Difference between current barrel location and aim direction
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotate = AimAsRotator - BarrelRotation;
	// Raise or lower barrel to aim direction
	Barrel->Elevate(DeltaRotate.Pitch);
	// Rotate turret towards aim direction in shortest direction
	if (FMath::Abs(DeltaRotate.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotate.Yaw);
	}
	else // Avoid going long way
	{
		Turret->Rotate(-DeltaRotate.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	FVector BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::Fire()
{
	// if time passed for reload, fire
	if (FiringStatus != EFiringStatus::Reloading && AmmoAmount > 0)
	{
		// check for barrel and projectile blueprint, do here, since we don't allow firing until reloaded
		if (!ensure(Barrel && ProjectileBP)) { return; }
		// Spawn a projectile at end barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		AmmoAmount -= 1;
	}
}