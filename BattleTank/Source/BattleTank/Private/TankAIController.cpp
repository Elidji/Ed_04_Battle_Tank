// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/Tank.h" // so we can implement OnDeath

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		// do here, may not yet have possessed pawn in begin play
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)){ return; }

		// subscribe  our local method to the tank
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	if (!GetPawn()) { return; }

	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Could also do GetWorld()->GetFirstPlayerController, this is more generalized
	// Note tank is a pawn, so we can keep this generalized, no need to cast as a tank
	APawn* PlayerTank = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
	// get the AI tanks aiming component
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(PlayerTank && AimingComponent)) { return; }

	// move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// aim at player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// fire at player if locked
	if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
	{
		AimingComponent->Fire();
	}
}