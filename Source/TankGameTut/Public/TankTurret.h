// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKGAMETUT_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed, +1 is max upward speed
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20;	
	
	
};
