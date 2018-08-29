// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	// register delegate - called every frame that has a hit, so every frame since always contacting ground
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// Drive Tracks
	DriveTrack();
	// Correct Sideways Movement
	ApplySidewaysForce();
	// reset throttle
	CurrentThrottle = 0;

}

void UTankTrack::ApplySidewaysForce()
{
	// get amount moving sideways - cosine is speed
	float SidewaysSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	/* figure out acceleration (speed / time) correction to correct - need a vector so multiple by right vector. 
	* That's the acceleration its going sideways, however we don't want to go sideways, want to counter
	* hence the -SidewaysSpeed
	*/ 
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector AccelerationCorrection = (-SidewaysSpeed / DeltaTime) * GetRightVector();

	// Apply counter force (F = m a)
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	FVector CounterForce = (TankRoot->GetMass() * AccelerationCorrection) / 2;  // divide by 2 because 2 tracks
	TankRoot->AddForce(CounterForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	// keeps between -1 and 1
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
	DriveTrack();
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	// get this component the track, then get the root which is the scene/tank. This can't have movement applied, so cast to primitive component
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

