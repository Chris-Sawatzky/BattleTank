// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
//Depends on movement component via pathfinding


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankAIController::Tick(float time)
{
	Super::Tick(time);

	//auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	//auto PlayerTank = Cast<ATank>(PlayerPawn);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	//Aim towards the player
	ControlledTank->FindComponentByClass<UTankAimingComponent>()->AimAt(PlayerTank->GetActorLocation());
	//ControlledTank->AimAt(PlayerTank->GetActorLocation());


	ControlledTank->FindComponentByClass<UTankAimingComponent>()->Fire();

	
}
