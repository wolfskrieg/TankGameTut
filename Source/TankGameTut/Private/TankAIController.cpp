// Fill out your copyright notice in the Description page of Project Settings.

#include "TankGameTut.h"
#include "../Public/TankAIController.h"
#include "Tank.h"

ATank* ATankAIController::GetPossessedTank() const {

	return Cast<ATank>(GetPawn());

}

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	if (GetPossessedTank()) {
	
		FString Print = GetPossessedTank()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("AI possessed tank is: %s"), *Print);
	
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("AI does not possess a tank."));
	
	}
	if (!GetPlayerTank()) {

		UE_LOG(LogTemp, Warning, TEXT("AI Tank does not see a Player"));

	}
	else {

		FString PlayerTankName = GetPlayerTank()->GetName();
		FString ThisTankName = Cast<ATank>(GetPawn())->GetName();
		UE_LOG(LogTemp, Warning, TEXT("AI Tank %s found player %s"), *ThisTankName, *PlayerTankName);

	}
}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {
	
		GetPossessedTank()->AimAt(GetPlayerTank()->GetActorLocation());

	}	
}

ATank* ATankAIController::GetPlayerTank() const {

	APawn* PlayerTankPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	ATank* TankPlayer = Cast<ATank>(PlayerTankPawn);
	if (!TankPlayer) {

		return nullptr;

	} else {

		return TankPlayer;

	}

}


