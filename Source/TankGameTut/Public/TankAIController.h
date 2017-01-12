// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class TANKGAMETUT_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	
	ATank* GetPossessedTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float ) override;
	ATank* GetPlayerTank() const;
	
	
};
