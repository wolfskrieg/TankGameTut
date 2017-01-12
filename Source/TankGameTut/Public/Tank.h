// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;

UCLASS()
class TANKGAMETUT_API ATank : public APawn
{
	GENERATED_BODY()

public:

	void AimAt(FVector HitLocation);

protected:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel *Barrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret *Turret);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000;
	
	
};
