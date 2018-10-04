// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
// Forward Declaration
class UTankBarrel;
class UTurret;

// Holds Barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation, float LaunchSpeed);

	void SetTurretReference(UTurret* TurretToSet);

	void SetBarrelReference(UTankBarrel* BarrelToSet);


private:
	UTankBarrel * Barrel = nullptr;
	UTurret * Turret = nullptr;

	void MoveBarrel(FVector AimDirection);
		
	
};