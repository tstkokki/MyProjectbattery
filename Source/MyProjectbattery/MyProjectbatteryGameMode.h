// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProjectbatteryGameMode.generated.h"

//enum to store the current state of gameplay
UENUM(BlueprintType)
enum class EBatteryPlayState:uint8
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};


UCLASS(minimalapi)
class AMyProjectbatteryGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyProjectbatteryGameMode();

	virtual void Tick(float DeltaTime) override;

	//returns power needed to for the HUD
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() { return this->PowerToWin; };

	virtual void BeginPlay() override;

	//Returns the current playing state
	UFUNCTION(BlueprintPure, Category = "Power")
	EBatteryPlayState GetCurrentState() const;

	//sets a new playing state
	void SetCurrentState(EBatteryPlayState NewState);

protected:
	// rate of power loss
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float DecayRate;

	// the power needed to win the game
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float PowerToWin;

	//the widget class to use for our HUD screen
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	// the instance of the HUD
	UPROPERTY()
	class UUserWidget* CurrentWidget;


private:
	// keep track of the current playing state
	EBatteryPlayState CurrentState;

	// Array to hold all the spawn volumes
	TArray<class ASpawnVolume*> SpawnVolumeActors;

	//handle any function calls that rely upon changing the playing state
	void HandleNewState(EBatteryPlayState NewState);
};



