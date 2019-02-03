// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	//delay spawning of actor until the end of begin play
	auto NewActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());//!!must call FinishSpawningActor when using SpawnActorDeferred!!
	if (!NewActor)
	{
		return;
	}
	//the new actor created off of the SpawnClass is being attached to the spawn point
	NewActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	//finish spawning the actor
	UGameplayStatics::FinishSpawningActor(NewActor, GetComponentTransform());
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

