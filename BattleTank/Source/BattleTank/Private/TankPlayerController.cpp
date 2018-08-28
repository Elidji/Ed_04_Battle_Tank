// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankPlayerController.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/Tank.h" // so we can use delegate for tank death

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// look through tank to grab an aiming component if attached - note tank is just a pawn, 
	// that's why we don't need to specifically grab the tank
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	// make sure component found before reporting its found
	if (ensure(AimingComponent)) { FoundAimingComponent(AimingComponent); }
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		// do here, may not yet have possessed pawn in begin play
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// subscribe  our local method to the tank
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("player tank died."));
}

void ATankPlayerController::AimTowardsCrosshair()
{
	// look through tank to grab an aiming component if attached - note tank is just a pawn, 
	// that's why we don't need to specifically grab the tank
	if (!GetPawn()) { return; } // not possessed - ie open blueprint, or die in game
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) { FoundAimingComponent(AimingComponent); }
	
	FVector HitLocation;
	// check if we hit the landscape - passing by reference
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	// cross hair position
	FVector2D CrosshairPosition = FVector2D(ViewportSizeX / 2, ViewportSizeY / 3.33333);
	FHitResult HitResult;
	bool bHit;
	// this does the de-projection and gets the 3d position. Note: no distance limit to the ray cast it does, 
	bHit = GetHitResultAtScreenPosition(CrosshairPosition, ECollisionChannel::ECC_Visibility, false, HitResult);
	if (bHit) {HitLocation = HitResult.ImpactPoint;}

	// Draws a red line for debugging purposes - #include "DrawDebugHelpers.h"
	// DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor::Red);

	return bHit;
}
