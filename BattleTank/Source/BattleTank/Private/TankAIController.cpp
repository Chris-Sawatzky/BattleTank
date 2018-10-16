// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

//get a reference to itself (AI Tank), or rather the possessed tank

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankAIController::Tick(float time)
{
	Super::Tick(time);

	//auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	//auto PlayerTank = Cast<ATank>(PlayerPawn);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank) 
	{
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		//Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		ControlledTank->Fire();
	}

	
}
