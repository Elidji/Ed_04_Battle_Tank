// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToASet)
{
	Barrel = BarrelToASet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	// grab the socket location from the barrel, placed at end of barrel in unreal
	auto BarrelLocation = Barrel->GetSocketLocation(FName("Projectile"));
	// our direction to fire
	FVector LaunchVelocity;
	TArray<AActor*> ActorList;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,            // just a reference to our tank aim component
		LaunchVelocity,  // pass by reference to get aim direction
		BarrelLocation,  // start
		HitLocation,     // end
		LaunchSpeed,     // speed
		ESuggestProjVelocityTraceOption::DoNotTrace   // don't trace along path for interferring objects
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

	Barrel->Elevate(5);
}