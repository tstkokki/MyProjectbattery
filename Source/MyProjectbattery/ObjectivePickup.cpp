// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "ObjectivePickup.h"

AObjectivePickup::AObjectivePickup() 
{
	GetMesh()->SetSimulatePhysics(true);
	//default score yield
	ScoreAmount = 1;
}

void AObjectivePickup::WasCollected_Implementation() 
{
	Super::WasCollected_Implementation();
	Destroy();
}

// return score yield
int AObjectivePickup::GetScore()
{
	return this->ScoreAmount;
}
