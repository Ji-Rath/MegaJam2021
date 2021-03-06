// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData.h"
#include "ItemBaseWidget.generated.h"

class UItemData;
class UGridPanel;
class UInventoryBaseWidget;

/**
 * 
 */
UCLASS()
class MEGAJAM2021_API UItemBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UItemBaseWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void ConstructGrid(FIntVector2D Size);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	UItemData* ItemData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	FIntVector2D Position;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	UInventoryBaseWidget* InventoryWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> SlotWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UGridPanel* GridTiles = nullptr;

};
