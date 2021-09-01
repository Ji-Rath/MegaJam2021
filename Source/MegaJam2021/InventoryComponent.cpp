// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ItemData.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Inventory.AddDefaulted(InventorySize.X * InventorySize.Y);
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
			OnItemAdded.Broadcast(Item, Position);
			SpawnWidgetItem(Item, Position);
			return true;
		}
	}

	return false;
}

bool UInventoryComponent::AddToSlot(UItemData* Item, FIntVector2D Position)
{
	bool bCanPlaceItem = HasAvailableSpace(Position, Item->Size);

	if (bCanPlaceItem)
	{
		OnItemAdded.Broadcast(Item, Position);
		SpawnWidgetItem(Item, Position);
		return true;
	}

	return false;
}

void UInventoryComponent::SetOccupied(bool bOccupied, TArray<FIntVector2D> Positions)
{
	for (FIntVector2D SlotPos : Positions)
	{
		int SlotIndex = PosToIndex(SlotPos);
		Inventory[SlotIndex].bTaken = bOccupied;
		UE_LOG(LogTemp, Log, TEXT("SLOT (%d, %d) HAS NOW BEEN TAKEN!"), SlotPos.X, SlotPos.Y);
	}
}

TArray<FIntVector2D> UInventoryComponent::GetSpaceTaken(FIntVector2D Size, FIntVector2D Position)
{
	TArray<FIntVector2D> FreeSlots;

	for (int XPos = Position.X; XPos < Size.X + Position.X; XPos++)
	{
		for (int YPos = Position.Y; YPos < Size.Y + Position.Y; YPos++)
		{
			FreeSlots.Add(FIntVector2D(XPos, YPos));
		}
	}

	return FreeSlots;
}

bool UInventoryComponent::HasAvailableSpace(FIntVector2D Position, FIntVector2D ItemSize)
{
	TArray<FIntVector2D> FreeSlots;

	for (int XPos = Position.X; XPos < ItemSize.X+Position.X; XPos++)
	{
		if (XPos < InventorySize.X)
		{
			for (int YPos = Position.Y; YPos < ItemSize.Y+Position.Y; YPos++)
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
					else
					{
						FreeSlots.Add(FIntVector2D(XPos, YPos));
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

	SetOccupied(true, FreeSlots);

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

	ReturnPosition.Y = Index / InventorySize.X;
	ReturnPosition.X = Index % InventorySize.X;

	return ReturnPosition;
}

