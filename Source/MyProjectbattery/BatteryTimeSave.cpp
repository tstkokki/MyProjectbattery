// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryTimeSave.h"

UBatteryTimeSave::UBatteryTimeSave() {

	SavedTime = 60.0f;
}

void UBatteryTimeSave::CheckNewTime(float _newTime)
{
	if (_newTime < SavedTime)
		SavedTime = _newTime;
}
