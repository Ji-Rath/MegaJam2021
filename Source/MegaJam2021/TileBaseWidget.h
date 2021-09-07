// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData.h"
#include "TileBaseWidget.generated.h"

class UInventoryBaseWidget;

/**
 * 
 */
UCLASS()
class MEGAJAM2021_API UTileBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintCallable)
	bool OnPlaceItem(FGeometry Geometry, FPointerEvent PointerEvent, UDragDropOperation* Operation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryBaseWidget* InventoryWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	FIntVector2D Position;
};
