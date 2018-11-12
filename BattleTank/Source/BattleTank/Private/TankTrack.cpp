// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Called OnHit"))
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//good practice to make sure that you have this Super::TickComponent();

	//calculate the slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// work-out the required acceleration this fram to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	// calculate and apply sideways force
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // two tracks
	TankRoot->AddForce(CorrectionForce);
}

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


