// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlsBaseWidget.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "SettingsSaveGame.h"
#include "GameFramework/SaveGame.h"
#include "CharacterController.h"
#include "EngineUtils.h"

void UControlsBaseWidget::RebindAxisMap(FName AxisName, float Scale, FInputChord NewKey)
{
	FInputAxisKeyMapping RebindedAxisMapping = FInputAxisKeyMapping(AxisName, NewKey.Key, Scale);

	if (ensure(SaveSettings))
	{
		TArray<FControlSaveSettings> RemoveSettings;
		for (FControlSaveSettings OldSaveSettings : SaveSettings->SaveControls)
		{
			if (OldSaveSettings.NewAxisMapping.AxisName == RebindedAxisMapping.AxisName && OldSaveSettings.NewAxisMapping.Scale == RebindedAxisMapping.Scale)
			{
				RemoveSettings.Add(OldSaveSettings);
			}
		}
		for (FControlSaveSettings RemoveSetting : RemoveSettings)
		{
			SaveSettings->SaveControls.Remove(RemoveSetting);
		}

		FControlSaveSettings ControlSettings(RebindedAxisMapping);
		SaveSettings->SaveControls.Add(ControlSettings);

		UGameplayStatics::SaveGameToSlot(SaveSettings, "Settings", 0);

		// Iterate over all actors, can also supply a different base class if needed
		for (TActorIterator<ACharacterController> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			// Follow iterator object to my actual actor pointer
			ACharacterController* PlayerController = *ActorItr;

			if (IsValid(PlayerController))
			{
				PlayerController->UpdateKeyBindings(SaveSettings->SaveControls);
			}
		}
	}
}

void UControlsBaseWidget::RebindActionMap(FName ActionName, FInputChord NewKey)
{
	FInputActionKeyMapping RebindedActionMapping(ActionName, NewKey.Key);

	if (ensure(SaveSettings))
	{
		TArray<FControlSaveSettings> RemoveSettings;
		for (FControlSaveSettings OldSaveSettings : SaveSettings->SaveControls)
		{
			if (OldSaveSettings.NewActionMapping.ActionName == RebindedActionMapping.ActionName)
			{
				RemoveSettings.Add(OldSaveSettings);
			}
		}
		for (FControlSaveSettings RemoveSetting : RemoveSettings)
		{
			SaveSettings->SaveControls.Remove(RemoveSetting);
		}

		FControlSaveSettings ControlSettings(RebindedActionMapping);
		SaveSettings->SaveControls.Add(ControlSettings);

		UGameplayStatics::SaveGameToSlot(SaveSettings, "Settings", 0);

		// Iterate over all actors, can also supply a different base class if needed
		for (TActorIterator<ACharacterController> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			// Follow iterator object to my actual actor pointer
			ACharacterController* PlayerController = *ActorItr;

			if (IsValid(PlayerController))
			{
				PlayerController->UpdateKeyBindings(SaveSettings->SaveControls);
			}
		}
	}
}

bool UControlsBaseWidget::Initialize()
{
	bool bSuccess = Super::Initialize();
	
	bool bSaveExists = UGameplayStatics::DoesSaveGameExist("Settings", 0);
	if (bSaveExists)
	{
		USaveGame* SaveGame = UGameplayStatics::LoadGameFromSlot("Settings", 0);
		SaveSettings = Cast<USettingsSaveGame>(SaveGame);
	}
	else
	{
		USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(USettingsSaveGame::StaticClass());
		SaveSettings = Cast<USettingsSaveGame>(SaveGame);
	}

	return bSuccess;
}
