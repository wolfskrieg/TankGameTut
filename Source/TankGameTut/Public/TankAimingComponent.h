// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

// Holds barrel's properties and elevate
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAMETUT_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetTurretReference(UTankTurret *Turret);
	void SetBarrelReference(UTankBarrel *Barrel);
	void AimAt(FVector& HitLocation, float LaunchSpeed);
	
private:

	void MoveBarrelAndTurret(FVector AimDirection);

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	
};
