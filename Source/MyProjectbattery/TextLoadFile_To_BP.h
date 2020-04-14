// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <Runtime\Core\Public\Misc\FileHelper.h>
#include "TextLoadFile_To_BP.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECTBATTERY_API UTextLoadFile_To_BP : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "file I/O")
		static FString LoadFileToString(FString _filename);

		UFUNCTION(BlueprintCallable, Category = "file I/O")
		static FString SaveFileToString(FString _filename, float _time);

		UFUNCTION(BlueprintCallable, Category = "file I/O")
		static TArray<FString> LoadFileToStringArray(FString _filename);
};
