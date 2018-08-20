// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankMovementComponent.h"
#include "../Public/TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// no need to call super, replacing functionality completely

	// Unit vector in direction tank would like to move
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	// the x direction
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	// want the dot product to get angle between forward x direction and intended direction
	float ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	// get cross product to see how much need to turn
	FVector RightThrow = FVector::CrossProduct(AIForwardIntention, TankForward);
	IntendMoveForward(ForwardThrow);
	IntendTurnRight(RightThrow.Z);
}
