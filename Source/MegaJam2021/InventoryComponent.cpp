// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ItemData.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::TryAddItem(UItemData* Item)
{
	for (int SlotNum = 0; SlotNum < Inventory.Num(); SlotNum++)
	{
		FSlotData Slot = Inventory[SlotNum];
		FIntVector2D Position = IndexToPos(SlotNum);
		bool bCanPlaceItem = HasAvailableSpace(Position, Item->Size);

		if (bCanPlaceItem)
		{
			
			return true;
		}
	}

	return false;
}

bool UInventoryComponent::HasAvailableSpace(FIntVector2D Position, FIntVector2D ItemSize)
{
	
	for (int XPos = Position.X; XPos < ItemSize.X; XPos++)
	{
		if (XPos < InventorySize.X)
		{
			for (int YPos = Position.Y; YPos < ItemSize.Y; YPos++)
			{
				//First make sure slot that we are checking is not out of bounds
				if (YPos < InventorySize.Y)
				{
					int IndexToCheck = PosToIndex(FIntVector2D(XPos, YPos));
					FSlotData SlotCheck = Inventory[IndexToCheck];
					if (SlotCheck.bTaken)
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

int UInventoryComponent::PosToIndex(FIntVector2D Position)
{
	int ReturnIndex = 0;
	ReturnIndex += Position.X;
	ReturnIndex += Position.Y * InventorySize.X;

	return ReturnIndex;

}

FIntVector2D UInventoryComponent::IndexToPos(int Index)
{
	FIntVector2D ReturnPosition;

	ReturnPosition.X = Index / InventorySize.X;
	ReturnPosition.Y = Index % InventorySize.X;

	return ReturnPosition;
}

