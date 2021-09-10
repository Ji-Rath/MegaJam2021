// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlsBaseWidget.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "SettingsSaveGame.h"
#include "GameFramework/SaveGame.h"
#include "CharacterController.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerInput.h"



bool UControlsBaseWidget::Initialize()
{
	bool bSuccess = Super::Initialize();

	return bSuccess;
}


