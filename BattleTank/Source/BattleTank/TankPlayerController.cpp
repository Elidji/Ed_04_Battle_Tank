// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	if (!Tank)
	{
		UE_LOG(LogTemp, Error, TEXT("The Tank is not controlled."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The Tank controlled is: %s"), *Tank->GetName());
	}
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

