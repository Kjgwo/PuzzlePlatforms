// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformsTrigger.h"
#include "Components/BoxComponent.h"

// Sets default values
APlatformsTrigger::APlatformsTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (!ensure(TriggerVolume != nullptr)) return;
	RootComponent = TriggerVolume;

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

