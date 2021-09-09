// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerInput.h"
#include "ControlsBaseWidget.generated.h"

class USettingsSaveGame;

/**
 * 
 */
UCLASS()
class MEGAJAM2021_API UControlsBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// TODO: Address binding multiple keybindings
	UFUNCTION(BlueprintCallable)
	void RebindAxisMap(FName AxisName, float Scale, FInputChord NewKey);

	UFUNCTION(BlueprintCallable)
	void RebindActionMap(FName ActionName, FInputChord NewKey);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USettingsSaveGame* SaveSettings;

	bool Initialize() override;

};
