// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
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
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		// move the barrel
		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	// Difference between current barrel location and aim direction
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotate = AimAsRotator - BarrelRotation;
	// Raise or lower barrel to aim direction
	Barrel->Elevate(DeltaRotate.Pitch);
	// Rotate turret towards aim direction
	Turret->Rotate(DeltaRotate.Yaw);
}