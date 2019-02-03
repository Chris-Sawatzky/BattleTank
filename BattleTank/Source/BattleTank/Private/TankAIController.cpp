// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h" // So we can implement OnDeath
//Depends on movement component via pathfinding


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; }

		//Subscribe our local method to the tanks death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}


void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn())
	{
		return;
	}
	GetPawn()->DetachFromControllerPendingDestroy();
}


void ATankAIController::Tick(float time)
{
	Super::Tick(time);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!(PlayerTank && ControlledTank)) { return; }
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	//Aim towards the player
	ControlledTank->FindComponentByClass<UTankAimingComponent>()->AimAt(PlayerTank->GetActorLocation());
	
	//if the firing state is Locked IE aiming at the player tank, the AI tank will fire
	if (ControlledTank->FindComponentByClass<UTankAimingComponent>()->GetFiringState() == EFiringStates::Locked)
	{
		ControlledTank->FindComponentByClass<UTankAimingComponent>()->Fire();
	}
	
}
