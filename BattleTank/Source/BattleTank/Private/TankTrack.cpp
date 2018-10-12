// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{

	//TODO Clamp actual trottle value

	// Calculation of force to be applied
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	// Location of what to apply the force to
	auto ForceLocation = GetComponentLocation();
	//Get the root component of the tank and cast that to a primitive component (you cannot add force to a root component)
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	// Add force to the primitive component of the tank
	TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);

}


