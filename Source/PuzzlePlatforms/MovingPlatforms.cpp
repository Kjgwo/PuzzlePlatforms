// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatforms.h"

AMovingPlatforms::AMovingPlatforms()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatforms::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) { 
		SetReplicates(true); 
		SetReplicateMovement(true); 
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatforms::Tick(float dt)
{
	Super::Tick(dt);

	if (HasAuthority()) {
		FVector Location = GetActorLocation();
		float journeyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float journeyTravelied = (Location - GlobalStartLocation).Size();

		if (journeyTravelied >= journeyLength) 
		{
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
		}
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += Speed * dt * Direction;
		SetActorLocation(Location);
	}
}
