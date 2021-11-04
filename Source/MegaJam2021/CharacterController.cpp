// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "GameFramework/SaveGame.h"
#include "SettingsSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerInput.h"
#include "SaveGameSubsystem.h"
#include "Engine/GameInstance.h"



void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (ensure(GameInstance))
	{
		USaveGameSubsystem* SaveGameSubsystem = GameInstance->GetSubsystem<USaveGameSubsystem>();
		if (ensure(SaveGameSubsystem))
		{
			SaveGameSubsystem->OnActionKeyChanged.AddDynamic(this, &ACharacterController::UpdateActionKey);
			SaveGameSubsystem->OnAxisKeyChanged.AddDynamic(this, &ACharacterController::UpdateAxisKey);
			SaveGameSubsystem->OnResetBindings.AddDynamic(this, &ACharacterController::ResetKeyBindings);
		}
	}
}

void ACharacterController::InitInputSystem()
{
	Super::InitInputSystem();
	// Use PlayerInput to set new input for this player controller

	if (UGameplayStatics::DoesSaveGameExist("Settings", 0))
	{
		USaveGame* GameSave = UGameplayStatics::LoadGameFromSlot("Settings", 0);
		USettingsSaveGame* SettingsSave = Cast<USettingsSaveGame>(GameSave);

		if (SettingsSave)
		{
			for (FInputAxisKeyMapping AxisKey : SettingsSave->GetModifiedAxisKeys())
			{
				UpdateAxisKey(AxisKey);
			}
			for (FInputActionKeyMapping ActionKey : SettingsSave->GetModifiedActionKeys())
			{
				UpdateActionKey(ActionKey);
			}
		}
	}

}

void ACharacterController::UpdateAxisKey(FInputAxisKeyMapping NewAxisKey)
{
	// Remove axis mapping that has equivalent scale
	FInputAxisKeyMapping OldAxisMapping = USaveGameSubsystem::GetAxisKeyMapping(PlayerInput, NewAxisKey.AxisName, NewAxisKey.Scale);
	PlayerInput->RemoveAxisMapping(OldAxisMapping);

	// Add new axis mapping
	PlayerInput->AddAxisMapping(NewAxisKey);

	PlayerInput->ForceRebuildingKeyMaps(false);
}

void ACharacterController::UpdateActionKey(FInputActionKeyMapping NewActionKey)
{
	// Remove axis mapping that has equivalent scale
	FInputActionKeyMapping OldActionMapping = USaveGameSubsystem::GetActionKeyMapping(PlayerInput, NewActionKey.ActionName);
	PlayerInput->RemoveActionMapping(OldActionMapping);

	// Add new action mapping
	PlayerInput->AddActionMapping(NewActionKey);

	PlayerInput->ForceRebuildingKeyMaps(false);
}

UPlayerInput* ACharacterController::GetPlayerInput() const
{
	return PlayerInput;
}

void ACharacterController::ResetKeyBindings()
{
	PlayerInput->ForceRebuildingKeyMaps(true);
}
