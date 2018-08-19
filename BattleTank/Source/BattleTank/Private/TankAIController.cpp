// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "../Public/Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AITank = Cast<ATank>(GetPawn());
	if (!AITank) { UE_LOG(LogTemp, Error, TEXT("The AI Tank is not controlled.")); }

	// Could also do GetWorld()->GetFirstPlayerController, this is more generalized
	// Note this returns a nullptr if doesn't exist, so don't need to do a check and return a nullptr
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	if (!PlayerTank) { UE_LOG(LogTemp, Error, TEXT("Can't find player tank.")); }
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerTank)
	{
		// aim at player
		AITank->AimAt(PlayerTank->GetActorLocation());

		// fire at player
		AITank->Fire();
	}
}