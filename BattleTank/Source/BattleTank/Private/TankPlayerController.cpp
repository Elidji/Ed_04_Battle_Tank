// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankPlayerController.h"
#include "../Public/Tank.h"
#include "DrawDebugHelpers.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	if (!Tank)
	{
		UE_LOG(LogTemp, Error, TEXT("The Tank is not controlled."));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	
	FVector HitLocation;
	// check if we hit the landscape - passing by reference
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
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

	// Draws a red line for debugging purposes
	// DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor::Red);

	return bHit;
}
