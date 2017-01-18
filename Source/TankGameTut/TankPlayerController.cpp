// Fill out your copyright notice in the Description page of Project Settings.

#include "TankGameTut.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
	
		FoundAimingComponent(AimingComponent);
	
	}
}

void ATankPlayerController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

void ATankPlayerController::AimTowardsCrosshair() {

	if (!ensure(AimingComponent)) { return; }
	FVector HitLocation;

	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if(bGotHitLocation) {
	
		AimingComponent->AimAt(HitLocation);

	}


}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector LookDirection;
	if (ensure(GetLookDirection(ScreenLocation, LookDirection))) {
	
		return GetLookVectorHitLocation(LookDirection, HitLocation);

	}
	else return false;
	
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {

	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
	


}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const  {

	FHitResult HitObject;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(
						
						HitObject, 
						StartLocation, 
						EndLocation, 
						ECollisionChannel::ECC_Visibility)
	) {

		HitLocation = HitObject.Location;
		return true;
	
	}
	else return false;
}

