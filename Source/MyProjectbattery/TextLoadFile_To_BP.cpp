// Fill out your copyright notice in the Description page of Project Settings.


#include "TextLoadFile_To_BP.h"
#include <Runtime/Core/Public/Misc/Paths.h>
#include <Runtime/Core/Public/HAL/PlatformFilemanager.h>

FString UTextLoadFile_To_BP::LoadFileToString(FString _filename)
{
	FString directory = FPaths::GameContentDir();
	FString result;
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();

	if (file.CreateDirectory(*directory)) {
		FString myFile = directory + "/" + _filename;
		FFileHelper::LoadFileToString(result, *myFile);
	}
	return result;
}

FString UTextLoadFile_To_BP::SaveFileToString(FString _filename, float _time)
{
	FString directory = FPaths::GameContentDir();
	FString result;
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();

	if (file.CreateDirectory(*directory)) {
		FString myFile = directory + "/" + _filename;
		result = FString::SanitizeFloat(_time);
		FFileHelper::SaveStringToFile(result, *myFile);
	}
	return result;
}

TArray<FString> UTextLoadFile_To_BP::LoadFileToStringArray(FString _filename)
{
	FString directory = FPaths::GameContentDir();
	TArray<FString> result;
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();

	if (file.CreateDirectory(*directory)) {
		FString myFile = directory + "/" + _filename;
		FFileHelper::LoadFileToStringArray(result, *myFile);
	}
	return result;
}
