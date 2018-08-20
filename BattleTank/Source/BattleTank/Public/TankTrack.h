// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 Tank Track is used to set maximum driving force and to apply force to tank
 */
UCLASS(ClassGroup = (Custom), meta= (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:

	// sets throttle between -1 and 1
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void SetThrottle(float Throttle);

	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TrackMaxDrivingForce = 10000000.0;// Assume 40 ton tank and 1g acceleration
	
};
