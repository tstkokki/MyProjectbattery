// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "SpawnVolume.h"
#include "Pickup.h"
#include "TimerManager.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	// Create the Box Component to represent the spawn volume
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

	//set the spawn delay range
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 4.5f;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomPointsInVolume()
{
	//get origin of the volume
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	//Get the extent of the volume
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	//return random point
	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ASpawnVolume::SetSpawningActive(bool bShouldSpawn)
{
	if(bShouldSpawn)
	{
		//Set the timer on spawn pickup
		//compute initial delay for the first spawn
		SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
		GetWorldTimerManager().SetTimer(this->SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
	}
	else 
	{
		//clear the timer
		GetWorldTimerManager().ClearTimer(this->SpawnTimer);
	}
}

void ASpawnVolume::SpawnPickup()
{
	// if the what to spawn is not NULL
	if (WhatToSpawn != NULL)
	{
		// Check for valid world
		UWorld* const World = GetWorld();
		if (World)
		{
			//Set the spawn parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			// get a random location to spawn at
			FVector SpawnLocation = GetRandomPointsInVolume();

			// get random rotation for the spawned item
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;


			//Spawn the pickup
			APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}

	// reset timer
	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
}
