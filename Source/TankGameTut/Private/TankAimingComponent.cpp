// Fill out your copyright notice in the Description page of Project Settings.

#include "TankGameTut.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* Barrel) {

	this->Barrel = Barrel;

}

void UTankAimingComponent::SetTurretReference(UTankTurret* Turret) {

	this->Turret = Turret;

}

void UTankAimingComponent::AimAt(FVector& HitLocation, float LaunchSpeed) {

	if (!Barrel || !Turret) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	// Calculating OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)	{
			FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
			MoveBarrelAndTurret(AimDirection);
			// UE_LOG(LogTemp, Warning, TEXT("Aim found"));
	}
	else {
	

		// UE_LOG(LogTemp, Warning, TEXT("Aim not found"));

	}

}

void UTankAimingComponent::MoveBarrelAndTurret(FVector AimDirection) {


	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator Aim = AimDirection.Rotation();
	FRotator DeltaRotatorBarrel = Aim - BarrelRotation;
	FRotator DeltaRotatorTurret = Aim - BarrelRotation;

	Barrel->Elevate(DeltaRotatorBarrel.Pitch);
	Turret->Rotate(DeltaRotatorTurret.Yaw);


}