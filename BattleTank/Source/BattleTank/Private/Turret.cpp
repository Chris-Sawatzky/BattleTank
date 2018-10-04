// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "Classes/Engine/World.h"

void UTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RotationChange + RelativeRotation.Yaw;

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}


