// Fill out your copyright notice in the Description page of Project Settings.

#include "TankGameTut.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"



void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {

	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}


void UTankMovementComponent::IntendMoveForward(float Throw) {

	if (!ensure(LeftTrack && RightTrack)) { 
		
		return; 
	
	} else {
	
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);

	}

}

void UTankMovementComponent::IntendRotateRight(float Throw) {

	if (!ensure(LeftTrack && RightTrack)) {

		return;

	}
	else {
	
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw);

	}

}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardVector = MoveVelocity.GetSafeNormal();
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardVector);
	float RightThrow = FVector::CrossProduct(AIForwardVector, TankForward).Z;
	IntendRotateRight(RightThrow);
	IntendMoveForward(ForwardThrow);
}

