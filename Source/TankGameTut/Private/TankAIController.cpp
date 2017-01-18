// Fill out your copyright notice in the Description page of Project Settings.

#include "TankGameTut.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	// Getting player tank
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();	
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if(ensure(PlayerTank) && ensure(AimingComponent)) {

		MoveToActor(PlayerTank, AcceptanceRadius);
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if ((AimingComponent->GetFiringStatus()) == EFiringStatus::Locked) 
		{		
			AimingComponent->Fire();
		}

	}


}
