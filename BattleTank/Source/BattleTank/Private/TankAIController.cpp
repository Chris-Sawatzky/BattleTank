// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

//get a reference to itself (AI Tank), or rather the possessed tank
ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"))
	}
	else
	{
		UE_LOG(LogTemp,Warning, TEXT("AIController found player: %s"), *(PlayerTank->GetName()))
	}
	
}

//gets a reference to the player tank (you)
ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }

	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float time)
{
	Super::Tick(time);

	if (GetPlayerTank()) 
	{
		// TODO Move towards the player

		//Aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//Fire if ready
	}

	
}
