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

public:

	AMovingPlatforms();

	virtual void Tick(float dt);

	UPROPERTY(EditAnywhere)

	float Speed = 30;
	
};
