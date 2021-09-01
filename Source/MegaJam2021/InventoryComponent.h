// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemData.h"
#include "InventoryComponent.generated.h"

class UGridPanel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemAdded, UItemData*, Item, FIntVector2D, Position);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FToggleInventory, bool, bOpen);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEGAJAM2021_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D InventorySize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSlotData> Inventory;

	UFUNCTION(BlueprintCallable)
	bool TryAddItem(UItemData* Item);

	UFUNCTION(BlueprintCallable)
	bool AddToSlot(UItemData* Item, FIntVector2D Position);

	UFUNCTION(BlueprintCallable)
	void SetOccupied(bool bOccupied, TArray<FIntVector2D> Positions);

	UFUNCTION(BlueprintCallable)
	TArray<FIntVector2D> GetSpaceTaken(FIntVector2D Size, FIntVector2D Position);

	UFUNCTION(BlueprintCallable)
	bool HasAvailableSpace(FIntVector2D Position, FIntVector2D ItemSize);

	UFUNCTION(BlueprintCallable)
	FIntVector2D IndexToPos(int Index);

	UFUNCTION(BlueprintCallable)
	int PosToIndex(FIntVector2D Position);

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnWidgetItem(UItemData* Item, FIntVector2D Position);

	UPROPERTY(BlueprintAssignable)
	FItemAdded OnItemAdded;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FToggleInventory OnToggleInventory;
};
