// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

UCLASS()
class TANKGAMETUT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent* AimingComponentReference);

private:
	
	virtual void BeginPlay() override;
	virtual void Tick(float) override;

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector&) const;
	bool GetLookDirection(FVector2D, FVector& WorldDirection) const;
	bool GetLookVectorHitLocation(FVector, FVector&) const;

	UPROPERTY(EditDefaultsOnly, Category = Crosshair)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = Crosshair)
	float CrosshairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly, Category = Crosshair)
	float LineTraceRange = 1000000.f;

	UTankAimingComponent* AimingComponent = nullptr;
	
};
