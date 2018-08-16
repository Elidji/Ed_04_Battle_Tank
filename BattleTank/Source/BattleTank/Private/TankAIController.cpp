// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AITank = GetAITank();
	if (!AITank) { UE_LOG(LogTemp, Error, TEXT("The AI Tank is not controlled.")); }

	PlayerTank = GetPlayerTank();
	if (!PlayerTank) { UE_LOG(LogTemp, Error, TEXT("Can't find player tank.")); }
}

ATank* ATankAIController::GetAITank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	// Could also do GetWorld()->GetFirstPlayerController, this is more generalized
	// Note this returns a nullptr if doesn't exist, so don't need to do a check and return a nullptr
	return Cast<ATank>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerTank)
	{
		// aim at player
		AITank->AimAt(PlayerTank->GetActorLocation());
	}
}