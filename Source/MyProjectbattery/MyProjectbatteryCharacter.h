// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyProjectbatteryCharacter.generated.h"

UCLASS(config=Game)
class AMyProjectbatteryCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** collection sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collection", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* CollectionSphere;
public:
	AMyProjectbatteryCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	// Accessor function for initial power
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetInitialPower();
	
	//Accessor function for current power
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetCurrentPower();
	
	// function to update character power
	// @param PowerChange this is the amount to change power, can be positive or negative
	UFUNCTION(BlueprintCallable, Category = "Power")
	void UpdatePower(float PowerChange);

	// Accessor function for initial score
	UFUNCTION(BlueprintPure, Category = "Objective")
		int GetInitialScore();

	//Accessor function for current score
	UFUNCTION(BlueprintPure, Category = "Objective")
		int GetCurrentScore();

	UFUNCTION(BlueprintCallable, Category = "Objective")
		void UpdateScore(int ScoreChange);



protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	//Called when we press a key
	UFUNCTION(BlueprintCallable, Category = "Pickups")
	void CollectPickups();

	// Initial power of the player at start
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float InitialPower;

	// Initial power of the player at start
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective", Meta = (BlueprintProtected = "true"))
		int InitialScore;

	// multiplier for character speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float SpeedFactor;

	// speed when the character's power level = 0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float BaseSpeed;

	UFUNCTION(BlueprintImplementableEvent, Category = "Power")
	void PowerChangeEffect();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	//returns collection sphere subobject
	FORCEINLINE class USphereComponent* GetCollectionSphere() const { return CollectionSphere; }

private:

	//current power of the player
	UPROPERTY(VisibleAnywhere, Category = "Power")
	float CurrentPower;

	//current power of the player
	UPROPERTY(VisibleAnywhere, Category = "Objective")
		int CurrentScore;
};

