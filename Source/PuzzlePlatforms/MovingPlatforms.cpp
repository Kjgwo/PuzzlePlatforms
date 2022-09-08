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

	if (ActiveTriggers > 0) // Trigger 작동 시
	{
		if(HasAuthority()) // Server 연결
		{
			FVector Location = GetActorLocation();
			float journeyLength = (GlobalTargetLocation - GlobalStartLocation).Size(); // Static Mesh component의 절대적인 위치 기준으로 하는 이동 거리
			float journeyTravelied = (Location - GlobalStartLocation).Size(); // Static Mesh Component의 현재 위치 기준으로 하는 이동 거리

			if (journeyTravelied >= journeyLength) // 이동 중인 거리가 총 이동거리를 벗어났을 때, Swap 함수를 이용하여 Static Mesh Component의 방향을 바꾼다.
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
}

void AMovingPlatforms::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatforms::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}
