// Fill out your copyright notice in the Description page of Project Settings.

#include "TankGameTut.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector HitLocation) {

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);

}

void ATank::SetBarrelReference(UTankBarrel *Barrel) {

	TankAimingComponent->SetBarrelReference(Barrel);
	this->Barrel = Barrel;

}

void ATank::SetTurretReference(UTankTurret *Turret) {

	TankAimingComponent->SetTurretReference(Turret);

}

void ATank::Fire() {

	UE_LOG(LogTemp, Warning, TEXT("Tank fired"));
	if (!Barrel) { return; }
	else {
	
		GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
	
	}

}
