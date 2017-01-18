// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;
/**
 * Responsible for driving the tank tracks
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent, BlueprintRead))
class TANKGAMETUT_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendRotateRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Movement)
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

private:
	// called from the pathfinding logic by the AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	UTankTrack* RightTrack = nullptr;
	UTankTrack* LeftTrack = nullptr;
	
};
