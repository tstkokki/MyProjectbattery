// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BatteryTimeSave.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECTBATTERY_API UBatteryTimeSave : public USaveGame
{
	GENERATED_BODY()

public:
	UBatteryTimeSave();

	UFUNCTION(BlueprintPure, Category = "Time")
		float GetSavedTimes() { return this->SavedTime; };
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time", Meta = (BlueprintProtected = "true"))
		float SavedTime;

	void CheckNewTime(float _newTime);
};
