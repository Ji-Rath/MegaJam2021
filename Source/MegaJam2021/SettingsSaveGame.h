// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameFramework/PlayerInput.h"
#include "SettingsSaveGame.generated.h"

class UPlayerInput;

/**
 * 
 */
UCLASS()
class MEGAJAM2021_API USettingsSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInputActionKeyMapping> ModifiedActionKeys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInputAxisKeyMapping> ModifiedAxisKeys;

	UFUNCTION(BlueprintCallable)
	TArray<FInputActionKeyMapping> GetModifiedActionKeys();

	UFUNCTION(BlueprintCallable)
	TArray<FInputAxisKeyMapping> GetModifiedAxisKeys();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bToggleCrouch = false;
};
