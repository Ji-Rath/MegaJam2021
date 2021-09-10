#include "SaveGameSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "SettingsSaveGame.h"
#include "CharacterController.h"
#include "GameFramework/InputSettings.h"

FInputAxisKeyMapping USaveGameSubsystem::GetAxisKeyMapping(UPlayerInput* PlayerInput, FName AxisName, float Scale)
{
	TArray<FInputAxisKeyMapping> OldMappings = PlayerInput->GetKeysForAxis(AxisName);
	for (FInputAxisKeyMapping AxisKeyMapping : OldMappings)
	{
		if (AxisKeyMapping.Scale == Scale)
		{
			return AxisKeyMapping;
		}
	}

	UInputSettings* InputSettings = UInputSettings::GetInputSettings();
	TArray<FInputAxisKeyMapping> AxisMappings;
	InputSettings->GetAxisMappingByName(AxisName, AxisMappings);
	for (FInputAxisKeyMapping AxisKey : AxisMappings)
	{
		if (AxisKey.Scale == Scale)
		{
			return AxisKey;
		}
	}

	return FInputAxisKeyMapping();
}

FInputActionKeyMapping USaveGameSubsystem::GetActionKeyMapping(UPlayerInput* PlayerInput, FName ActionName)
{
	TArray<FInputActionKeyMapping> OldMappings = PlayerInput->GetKeysForAction(ActionName);
	for (FInputActionKeyMapping ActionKeyMapping : OldMappings)
	{
		if (ActionKeyMapping.ActionName == ActionName)
		{
			return ActionKeyMapping;
		}
	}

	UInputSettings* InputSettings = UInputSettings::GetInputSettings();
	TArray<FInputActionKeyMapping> ActionMappings;
	InputSettings->GetActionMappingByName(ActionName, ActionMappings);
	for (FInputActionKeyMapping ActionKey : ActionMappings)
	{
		return ActionKey;
	}

	return FInputActionKeyMapping();
}

void USaveGameSubsystem::RebindAxisMap(FName AxisName, float Scale, FInputChord NewKey)
{
	FInputAxisKeyMapping RebindedAxisMapping = FInputAxisKeyMapping(AxisName, NewKey.Key, Scale);
	SaveSettings = GetGameSave<USettingsSaveGame>("Settings");

	if (ensure(SaveSettings))
	{
		TArray<FInputAxisKeyMapping> RemoveAxisKeys;
		TArray<FInputAxisKeyMapping> CurrentAxisKeys = SaveSettings->GetModifiedAxisKeys();

		// Remove existing axis key
		for (FInputAxisKeyMapping AxisKey : CurrentAxisKeys)
		{
			if (AxisKey.AxisName == RebindedAxisMapping.AxisName && AxisKey.Scale == RebindedAxisMapping.Scale)
			{
				RemoveAxisKeys.Add(AxisKey);
			}
		}
		for (FInputAxisKeyMapping AxisKey : RemoveAxisKeys)
		{
			CurrentAxisKeys.Remove(AxisKey);
		}

		// Add new axis key
		CurrentAxisKeys.Add(RebindedAxisMapping);
		SaveSettings->ModifiedAxisKeys = CurrentAxisKeys;

		// Save settings
		UGameplayStatics::SaveGameToSlot(SaveSettings, "Settings", 0);

		// Iterate over all character controllers
		for (TActorIterator<ACharacterController> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ACharacterController* PlayerController = *ActorItr;

			// Update character controller input bindings
			if (IsValid(PlayerController))
			{
				PlayerController->UpdateKeyBindings(CurrentAxisKeys);
			}
		}

		OnAxisKeyChanged.Broadcast(RebindedAxisMapping);
	}
}

void USaveGameSubsystem::RebindActionMap(FName ActionName, FInputChord NewKey)
{
	FInputActionKeyMapping RebindedActionMapping(ActionName, NewKey.Key);
	SaveSettings = GetGameSave<USettingsSaveGame>("Settings");

	if (ensure(SaveSettings))
	{
		TArray<FInputActionKeyMapping> RemoveActionKeys;
		TArray<FInputActionKeyMapping> CurrentActionKeys = SaveSettings->GetModifiedActionKeys();

		// Remove current action key
		for (FInputActionKeyMapping ActionKey : CurrentActionKeys)
		{
			if (ActionKey.ActionName == RebindedActionMapping.ActionName)
			{
				RemoveActionKeys.Add(ActionKey);
			}
		}
		for (FInputActionKeyMapping ActionKey : RemoveActionKeys)
		{
			CurrentActionKeys.Remove(ActionKey);
		}

		// Add new action key
		CurrentActionKeys.Add(RebindedActionMapping);
		SaveSettings->ModifiedActionKeys = CurrentActionKeys;

		// Save settings
		UGameplayStatics::SaveGameToSlot(SaveSettings, "Settings", 0);

		// Iterate over all character controllers
		for (TActorIterator<ACharacterController> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ACharacterController* PlayerController = *ActorItr;

			// Update character controller input bindings
			if (IsValid(PlayerController))
			{
				PlayerController->UpdateKeyBindings(CurrentActionKeys);
			}
		}

		OnActionKeyChanged.Broadcast(RebindedActionMapping);
	}
}

void USaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	SaveSettings = GetGameSave<USettingsSaveGame>("Settings");
}

void USaveGameSubsystem::ResetKeyBindings()
{
	SaveSettings = GetGameSave<USettingsSaveGame>("Settings");
	if (ensure(SaveSettings))
	{
		SaveSettings->ModifiedAxisKeys.Empty();
		SaveSettings->ModifiedActionKeys.Empty();

		// Save settings
		UGameplayStatics::SaveGameToSlot(SaveSettings, "Settings", 0);

		// Iterate over all character controllers
		for (TActorIterator<ACharacterController> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ACharacterController* PlayerController = *ActorItr;

			// Update character controller input bindings
			if (IsValid(PlayerController))
			{
				PlayerController->UpdateKeyBindings(SaveSettings->ModifiedAxisKeys);
				PlayerController->UpdateKeyBindings(SaveSettings->ModifiedActionKeys);
			}
		}

		OnActionKeyChanged.Broadcast(FInputActionKeyMapping());
		OnAxisKeyChanged.Broadcast(FInputAxisKeyMapping());
	}
}

USaveGame* USaveGameSubsystem::GetGameSave(FString SlotName, UClass* SaveType)
{
	bool bSaveExists = UGameplayStatics::DoesSaveGameExist(SlotName, 0);
	if (bSaveExists)
	{
		return UGameplayStatics::LoadGameFromSlot(SlotName, 0);
	}
	else
	{
		return UGameplayStatics::CreateSaveGameObject(SaveType->StaticClass());
	}
}

