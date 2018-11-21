// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Classes/Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	//reset the throttle to 0 to prevent the tank from moving after letting go of the controls
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	//calculate the slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// work-out the required acceleration this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	// calculate and apply sideways force
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	// Calculation of force to be applied
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	// Location of what to apply the force to
	auto ForceLocation = GetComponentLocation();
	//Get the root component of the tank and cast that to a primitive component (you cannot add force to a root component)
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	// Add force to the primitive component of the tank
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


