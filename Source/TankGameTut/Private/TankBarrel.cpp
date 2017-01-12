// Fill out your copyright notice in the Description page of Project Settings.

#include "TankGameTut.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Elevation = RelativeRotation.Pitch + ElevationChange;
	Elevation = FMath::ClampAngle(Elevation, MinElevationDegree, MaxElevationDegree);
	SetRelativeRotation(FRotator(Elevation, 0, 0));

}


