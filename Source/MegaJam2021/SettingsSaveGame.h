// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameFramework/PlayerInput.h"
#include "SettingsSaveGame.generated.h"

class UPlayerInput;

USTRUCT(Blueprintable)
struct FControlSaveSettings
{
	GENERATED_USTRUCT_BODY();

	// Save Axis mapping
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInputAxisKeyMapping NewAxisMapping;

	// Save Action mapping
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInputActionKeyMapping NewActionMapping;

	FControlSaveSettings() {};

	FControlSaveSettings(FInputActionKeyMapping ActionMapping)
	{
		NewActionMapping = ActionMapping;
	}

	FControlSaveSettings(FInputAxisKeyMapping AxisMapping)
	{
		NewAxisMapping = AxisMapping;
	}

	bool operator==(const FControlSaveSettings& Other) const
	{
		return (	NewAxisMapping == Other.NewAxisMapping
				|| NewActionMapping == Other.NewActionMapping);
	}
};

/**
 * 
 */
UCLASS()
class MEGAJAM2021_API USettingsSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FControlSaveSettings> SaveControls;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FText GetAxisKeyName(UPlayerInput* PlayerInput, FName AxisName, float Scale);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FInputAxisKeyMapping GetAxisKeyMapping(UPlayerInput* PlayerInput, FName AxisName, float Scale);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FInputActionKeyMapping GetActionKeyMapping(UPlayerInput* PlayerInput, FName AxisName);
};
