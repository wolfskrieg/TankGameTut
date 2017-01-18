// Fill out your copyright notice in the Description page of Project Settings.

#include "TankGameTut.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::BeginPlay()
{
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else 
	{
		FiringStatus = EFiringStatus::Locked;
	}
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	// checks if aimDirection and Barrel direction are equal, if they are, tank is locked instead of aiming
	return !Barrel->GetForwardVector().Equals(AimDirection, 0.01);
}


void UTankAimingComponent::AimAt(FVector HitLocation) 
{
	if (!ensure(Barrel && Turret)) { return; }
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
			AimDirection = OutLaunchVelocity.GetSafeNormal();
			MoveBarrelAndTurret(AimDirection);
	}

}

void UTankAimingComponent::Initialise(UTankBarrel * TankBarrel, UTankTurret * TankTurret)
{

	if (!ensure(TankBarrel && TankTurret)) { return; }
	Barrel = TankBarrel;
	Turret = TankTurret;


}

void UTankAimingComponent::Fire()
{
	
	if (FiringStatus != EFiringStatus::Reloading) {

		if (!ensure(Barrel && ProjectileBlueprint)) { return; }
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();

	}
	else return;
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

void UTankAimingComponent::MoveBarrelAndTurret(FVector AimDirection) {

	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator Aim = AimDirection.Rotation();
	FRotator DeltaRotator = Aim - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);
	if (DeltaRotator.Yaw > 180) {
	
		Turret->Rotate(-DeltaRotator.Yaw);
	
	}
	else Turret->Rotate(DeltaRotator.Yaw);


}
