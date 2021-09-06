// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData.h"
#include "InventoryBaseWidget.generated.h"

class UInventoryComponent;
class UGridPanel;
class UCanvasPanel;
class UWidgetAnimation;

/**
 * 
 */
UCLASS()
class MEGAJAM2021_API UInventoryBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	bool Initialize() override;

	UInventoryBaseWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void ConstructGrid(FIntVector2D Size);

	UFUNCTION(BlueprintCallable)
	void AddItem(UItemData* ItemData, FIntVector2D Position);

	UFUNCTION(BlueprintCallable)
	void ToggleInventory(bool bOpen);

	UFUNCTION(BlueprintCallable)
	void ReconstructItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> SlotWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ItemWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryComponent* InventoryReference = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UGridPanel* GridPanel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* CanvasPanel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UWidgetAnimation* FadeAnimation = nullptr;

};
