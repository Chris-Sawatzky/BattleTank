// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Tank.h"
#include "Engine/World.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	//TODO prevent double speed due to dual control use
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
	//TODO prevent double speed due to dual control use
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{	
	auto TankName = GetOwner()->GetName(); //REMEMBER THIS!!!! you get the tank name this way because you are in the component wich is part of (owned by) the tank
	UE_LOG(LogTemp, Warning, TEXT("%s's move velocity is %s"), *TankName, *(MoveVelocity.ToString()));
}



