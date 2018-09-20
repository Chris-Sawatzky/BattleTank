// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto AITank = GetControlledTank();
	if (!AITank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Not Possessed by AI Controller"))
	}
	else
	{
		UE_LOG(LogTemp,Warning, TEXT("%s possesed by AI Controller"), *(AITank->GetName()))
	}
	
}
