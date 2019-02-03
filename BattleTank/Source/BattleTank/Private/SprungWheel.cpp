// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint"));
	SetRootComponent(Constraint);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	//AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->SetupAttachment(Constraint); // only works in the constructor
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	SetupConstraint();

}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) { return; }
	//gets the parent that the SprungWheel is attached to (tank) and then gets the root component and cast it to a UPrimitiveComponent
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	Constraint->SetConstrainedComponents(BodyRoot, NAME_None, Wheel, NAME_None);
	UE_LOG(LogTemp, Warning, TEXT("BodyRoot: %s"), *BodyRoot->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Wheel: %s"), *Wheel->GetName());
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

