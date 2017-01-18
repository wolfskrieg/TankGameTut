// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class TANKGAMETUT_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;

protected:
	UPROPERTY(EDitDefaultsOnly, Category = RadiusOfFiring)
	float AcceptanceRadius = 8000;

private:
	APawn* ControlledTank;
	APawn* PlayerTank;
	
	
	
	UTankAimingComponent* AimingComponent = nullptr;
};
