// Fill out your copyright notice in the Description page of Project Settings.

#include "TankGameTut.h"
#include "TankPlayerController.h"
#include "Tank.h"


ATank* ATankPlayerController::GetControlledTank() const { return Cast<ATank>(GetPawn()); }

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Begin Play called"));
	
	if (GetControlledTank()) {

		FString Temporary = GetControlledTank()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Tank is: %s"), *Temporary);

	} else {
	
		UE_LOG(LogTemp, Warning, TEXT("There is no tank"));


	}

}

void ATankPlayerController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

void ATankPlayerController::AimTowardsCrosshair() {

	if (!GetControlledTank()) { return; }
	FVector HitLocation; 
	if (GetSightRayHitLocation(HitLocation)) {
	
		GetControlledTank()->AimAt(HitLocation);

	}



}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
	
		if (GetLookVectorHitLocation(LookDirection, HitLocation)) {
			
			return true;
		
		}
		else return false;
	
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