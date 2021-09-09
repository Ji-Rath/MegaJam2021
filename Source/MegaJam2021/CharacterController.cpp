// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "GameFramework/SaveGame.h"
#include "SettingsSaveGame.h"
#include "Kismet/GameplayStatics.h"



void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterController::InitInputSystem()
{
	Super::InitInputSystem();
	// Use PlayerInput to set new input for this player controller

	if (UGameplayStatics::DoesSaveGameExist("Settings", 0))
	{
		USaveGame* GameSave = UGameplayStatics::LoadGameFromSlot("Settings", 0);
		USettingsSaveGame* SettingsSave = Cast<USettingsSaveGame>(GameSave);
		UpdateKeyBindings(SettingsSave->SaveControls);
	}

}

void ACharacterController::UpdateKeyBindings(TArray<FControlSaveSettings> ControlBindings)
{

	for (FControlSaveSettings ControlSetting : ControlBindings)
	{
		if (ControlSetting.NewAxisMapping.AxisName != NAME_None)
		{
			// Remove axis mapping that has equivalent scale
			FInputAxisKeyMapping OldAxisMapping = USettingsSaveGame::GetAxisKeyMapping(PlayerInput, ControlSetting.NewAxisMapping.AxisName, ControlSetting.NewAxisMapping.Scale);
			PlayerInput->RemoveAxisMapping(OldAxisMapping);

			// Add new axis mapping
			PlayerInput->AddAxisMapping(ControlSetting.NewAxisMapping);
		}
		else if (ControlSetting.NewActionMapping.ActionName != NAME_None)
		{
			// Remove axis mapping that has equivalent scale
			FInputActionKeyMapping OldActionMapping = USettingsSaveGame::GetActionKeyMapping(PlayerInput, ControlSetting.NewActionMapping.ActionName);
			PlayerInput->RemoveActionMapping(OldActionMapping);

			// Add new action mapping
			PlayerInput->AddActionMapping(ControlSetting.NewActionMapping);
		}
	}
}

UPlayerInput* ACharacterController::GetPlayerInput() const
{
	return PlayerInput;
}
