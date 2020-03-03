// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MyProjectbatteryGameMode.h"
#include "MyProjectbatteryCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "SpawnVolume.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"

AMyProjectbatteryGameMode::AMyProjectbatteryGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//base decay rate
	DecayRate = 0.01f;

	// set the ticking functionality to true
	PrimaryActorTick.bCanEverTick = true;
}

void AMyProjectbatteryGameMode::Tick(float DeltaTime)
{
	// call the super's tick function
	Super::Tick(DeltaTime);

	// Get the character
	AMyProjectbatteryCharacter* MyCharacter = Cast<AMyProjectbatteryCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		/*switch (GetCurrentState())
		{

			default:
				break;
		}*/

		// if our power is greater than needed to win, set the state to won
		if (MyCharacter->GetCurrentPower() > PowerToWin)
		{
			SetCurrentState(EBatteryPlayState::EWon);
		}
		//if current power is positive
		if (MyCharacter->GetCurrentPower() > 0.0f)
		{
			//Drain the power, dependent on deltatime
			MyCharacter->UpdatePower(-DeltaTime * DecayRate * (MyCharacter->GetInitialPower()));
		}
		else
		{
			// Power is gone
			SetCurrentState(EBatteryPlayState::EGameOver);
		}
	}
	
}

void AMyProjectbatteryGameMode::BeginPlay()
{
	Super::BeginPlay();
	//find all spawn volume actors
	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for(auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}
	SetCurrentState(EBatteryPlayState::EPlaying);

	// set the score to beat
	AMyProjectbatteryCharacter* MyCharacter = Cast<AMyProjectbatteryCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		PowerToWin = (MyCharacter->GetInitialPower()) * 1.25f;
	}

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}

}

EBatteryPlayState AMyProjectbatteryGameMode::GetCurrentState() const
{
	return CurrentState;
}

void AMyProjectbatteryGameMode::SetCurrentState(EBatteryPlayState NewState)
{
	//set the current state
	CurrentState = NewState;
	//handle current state
	HandleNewState(CurrentState);
}

void AMyProjectbatteryGameMode::HandleNewState(EBatteryPlayState NewState)
{
	switch (NewState)
	{
		// if the game is playing
	case EBatteryPlayState::EPlaying:
	{
		// spawn volume active
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(true);
		}
	}
	break;
	// if we've won the game
	case EBatteryPlayState::EWon:
	{
		// spawn volume inactive
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(false);
		}
	}
	break;
	// if we've lost the game
	case EBatteryPlayState::EGameOver:
	{
		// spawn volume inactive
		for (auto spawnvol : SpawnVolumeActors)
		{
			spawnvol->SetSpawningActive(false);
		}
		//block player input
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			PlayerController->SetCinematicMode(true, false, false, true, true);
		}
		// ragdoll the character
		ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		if (MyCharacter)
		{
			MyCharacter->GetMesh()->SetSimulatePhysics(true);
			MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
		}
	}
	break;

	default:
	// unknown/default state 
	case EBatteryPlayState::EUnknown:
	{

	}
	break;
	}
}
