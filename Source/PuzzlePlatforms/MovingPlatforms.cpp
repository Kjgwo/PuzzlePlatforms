// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatforms.h"

AMovingPlatforms::AMovingPlatforms()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatforms::Tick(float dt)
{
	Super::Tick(dt);

	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		Location += FVector(Speed * dt, 0, 0); // 언리얼에서는 cm가 기본단위
		SetActorLocation(Location);
	}
}
