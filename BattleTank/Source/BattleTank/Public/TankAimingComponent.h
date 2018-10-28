// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringStates : uint8
{
	Reloading,
	Aiming,
	Locked
};

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

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTurret* TurretToSet, UTankBarrel* BarrelToSet);

	void AimAt(FVector HitLocation, float LaunchSpeed);

private:
	UTankBarrel * Barrel = nullptr;
	UTurret * Turret = nullptr;

	void MoveBarrel(FVector AimDirection);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStates FiringStates = EFiringStates::Aiming;
};
