// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

	// Called every frame - where aim at player happens
	virtual void Tick(float) override;

protected:

	virtual void BeginPlay() override;

private:

	// How close can AI tank get to player, in cm
	float AcceptanceRadius = 3000;
};
