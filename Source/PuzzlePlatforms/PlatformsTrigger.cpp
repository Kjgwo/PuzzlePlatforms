// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformsTrigger.h"

#include "Components/BoxComponent.h"

#include "MovingPlatforms.h"

// Sets default values
APlatformsTrigger::APlatformsTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (!ensure(TriggerVolume != nullptr)) return;

	RootComponent = TriggerVolume;

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformsTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformsTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APlatformsTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformsTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformsTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (AMovingPlatforms* Platform : PlatformsToTrigger)
	{
		Platform->AddActiveTrigger();
	}
}

void APlatformsTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (AMovingPlatforms* Platform : PlatformsToTrigger)
	{
		Platform->RemoveActiveTrigger();
	}
}

