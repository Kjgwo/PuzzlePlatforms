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

	if (ActiveTriggers > 0) // Trigger �۵� ��
	{
		if(HasAuthority()) // Server ����
		{
			FVector Location = GetActorLocation();
			float journeyLength = (GlobalTargetLocation - GlobalStartLocation).Size(); // Static Mesh component�� �������� ��ġ �������� �ϴ� �̵� �Ÿ�
			float journeyTravelied = (Location - GlobalStartLocation).Size(); // Static Mesh Component�� ���� ��ġ �������� �ϴ� �̵� �Ÿ�

			if (journeyTravelied >= journeyLength) // �̵� ���� �Ÿ��� �� �̵��Ÿ��� ����� ��, Swap �Լ��� �̿��Ͽ� Static Mesh Component�� ������ �ٲ۴�.
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
