// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
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

};
