// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "../Public/Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AITank = Cast<ATank>(GetPawn());
	// Could also do GetWorld()->GetFirstPlayerController, this is more generalized
	// Note this returns a nullptr if doesn't exist, so don't need to do a check and return a nullptr
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ensure(PlayerTank))
	{
		// move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);

		// aim at player
		AITank->AimAt(PlayerTank->GetActorLocation());

		// fire at player
		AITank->Fire();
	}
}