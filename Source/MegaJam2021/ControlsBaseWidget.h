// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControlsBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class MEGAJAM2021_API UControlsBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	bool Initialize() override;

	

};
