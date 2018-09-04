// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankTrack.h"
#include "../Public/SpringWheel.h"
#include "../Public/SpawnPoint.h"
#include "Components/SceneComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle)
{
	// keeps between -1 and 1
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	float ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	TArray<ASpringWheel*> Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASpringWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASpringWheel*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> Children;
	TArray<ASpringWheel*> Wheels;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SpringWheel = Cast<ASpringWheel>(SpawnedChild);
		if (!SpringWheel) continue;

		Wheels.Add(SpringWheel);
	}
	return Wheels;
}
