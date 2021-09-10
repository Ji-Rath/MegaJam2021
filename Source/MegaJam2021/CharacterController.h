// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerInput.h"
#include "SettingsSaveGame.h"
#include "CharacterController.generated.h"

/**
 * 
 */
UCLASS()
class MEGAJAM2021_API ACharacterController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;

public:
	void InitInputSystem() override;

	UFUNCTION()
	void UpdateActionKey(FInputActionKeyMapping NewActionKey);

	UFUNCTION()
	void UpdateAxisKey(FInputAxisKeyMapping NewAxisKey);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UPlayerInput* GetPlayerInput() const;

	UFUNCTION()
	void ResetKeyBindings();
};
