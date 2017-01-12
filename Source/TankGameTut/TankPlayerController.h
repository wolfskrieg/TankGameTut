// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;


UCLASS()
class TANKGAMETUT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank* GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float) override;

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector&) const;
	bool GetLookDirection(FVector2D, FVector& WorldDirection) const;
	bool GetLookVectorHitLocation(FVector, FVector&) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;
	
};
