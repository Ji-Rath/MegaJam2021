// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsSaveGame.h"
#include "GameFramework/PlayerInput.h"

FText USettingsSaveGame::GetAxisKeyName(UPlayerInput* PlayerInput, FName AxisName, float Scale)
{
	return GetAxisKeyMapping(PlayerInput, AxisName, Scale).Key.GetDisplayName(false);
}

FInputAxisKeyMapping USettingsSaveGame::GetAxisKeyMapping(UPlayerInput* PlayerInput, FName AxisName, float Scale)
{
	TArray<FInputAxisKeyMapping> OldMappings = PlayerInput->GetKeysForAxis(AxisName);
	for (FInputAxisKeyMapping AxisKeyMapping : OldMappings)
	{
		if (AxisKeyMapping.Scale == Scale)
		{
			return AxisKeyMapping;
		}
	}

	return FInputAxisKeyMapping();
}

FInputActionKeyMapping USettingsSaveGame::GetActionKeyMapping(UPlayerInput* PlayerInput, FName ActionName)
{
	TArray<FInputActionKeyMapping> OldMappings = PlayerInput->GetKeysForAction(ActionName);
	for (FInputActionKeyMapping ActionKeyMapping : OldMappings)
	{
		if (ActionKeyMapping.ActionName == ActionName)
		{
			return ActionKeyMapping;
		}
	}

	return FInputActionKeyMapping();
}
