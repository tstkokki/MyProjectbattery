// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "BatteryPickup.h"

//Set default value
ABatteryPickup::ABatteryPickup() 
{
	GetMesh()->SetSimulatePhysics(true);

	//default battery power
	BatteryPower = 200.0f;
}

void ABatteryPickup::WasCollected_Implementation()
{
	// use the base pickup behavior
	Super::WasCollected_Implementation();
	//Destroy the battery
	Destroy();
}
//returns battery power
float ABatteryPickup::GetPower()
{
	return this->BatteryPower;
}


