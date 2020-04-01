// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "ObjectivePickup.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECTBATTERY_API AObjectivePickup : public APickup
{
	GENERATED_BODY()
	
public:
	//set the default values for properties
	AObjectivePickup();
	// override WasCollected function
	void WasCollected_Implementation() override;

	int GetScore();


protected:
	// set the amount of power to yield to character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective", Meta = (BlueprintProtected = "true"))
		float ScoreAmount;

};
