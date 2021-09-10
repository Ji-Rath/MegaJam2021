// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "GameFramework/SaveGame.h"
#include "SettingsSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerInput.h"
#include "SaveGameSubsystem.h"



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

		UpdateKeyBindings(SettingsSave->GetModifiedAxisKeys());
		UpdateKeyBindings(SettingsSave->GetModifiedActionKeys());
	}

}

void ACharacterController::UpdateKeyBindings(TArray<FInputAxisKeyMapping> AxisMappings)
{
	for (FInputAxisKeyMapping AxisKey : AxisMappings)
	{
		// Remove axis mapping that has equivalent scale
		FInputAxisKeyMapping OldAxisMapping = USaveGameSubsystem::GetAxisKeyMapping(PlayerInput, AxisKey.AxisName, AxisKey.Scale);
		PlayerInput->RemoveAxisMapping(OldAxisMapping);

		// Add new axis mapping
		PlayerInput->AddAxisMapping(AxisKey);
	}
}

void ACharacterController::UpdateKeyBindings(TArray<FInputActionKeyMapping> ActionMappings)
{
	for (FInputActionKeyMapping ActionKey : ActionMappings)
	{
		// Remove axis mapping that has equivalent scale
		FInputActionKeyMapping OldActionMapping = USaveGameSubsystem::GetActionKeyMapping(PlayerInput, ActionKey.ActionName);
		PlayerInput->RemoveActionMapping(OldActionMapping);

		// Add new action mapping
		PlayerInput->AddActionMapping(ActionKey);
	}
}

UPlayerInput* ACharacterController::GetPlayerInput() const
{
	return PlayerInput;
}
