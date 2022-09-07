// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatforms.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatforms : public AStaticMeshActor
{
	GENERATED_BODY()
private:
	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;

public:

	AMovingPlatforms();

	virtual void BeginPlay() override;

	virtual void Tick(float dt) override;

	UPROPERTY(EditAnywhere)
	float Speed = 20;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation; // 로컬 기준의 Location 상대적인 위치

	void AddActiveTrigger();
	void RemoveActiveTrigger();

};
