// Fill out your copyright notice in the Description page of Project Settings.


#include "TileBaseWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemBaseWidget.h"
#include "InventoryComponent.h"
#include "ItemData.h"
#include "InventoryBaseWidget.h"

bool UTileBaseWidget::OnPlaceItem(FGeometry Geometry, FPointerEvent PointerEvent, UDragDropOperation* Operation)
{
	if (ensure(Operation && IsValid(Operation->Payload) && InventoryWidget))
	{
		// Retrieve payload from drag drop operation
		UItemBaseWidget* ItemWidget = Cast<UItemBaseWidget>(Operation->Payload);

		if (ensure(ItemWidget && ItemWidget->InventoryWidget))
		{
			// Get inventory component references
			UInventoryComponent* OtherInventoryComp = ItemWidget->InventoryWidget->InventoryReference;
			UInventoryComponent* InventoryComp = InventoryWidget->InventoryReference;

			if (ensure(ItemWidget && OtherInventoryComp && ItemWidget->ItemData && InventoryComp))
			{
				// Ensure the inventory that we are dropping the item to has space
				bool bHasSpace = InventoryComp->HasAvailableSpace(Position, ItemWidget->ItemData->Size);
				if (bHasSpace)
				{
					// Clear space from old inventory
					TArray<FIntVector2D> SpaceTaken = OtherInventoryComp->GetSpaceTaken(ItemWidget->ItemData->Size, ItemWidget->Position);
					OtherInventoryComp->SetOccupied(false, SpaceTaken);

					// Occupy new space
					SpaceTaken = InventoryComp->GetSpaceTaken(ItemWidget->ItemData->Size, Position);
					InventoryComp->SetOccupied(true, SpaceTaken);

					// Update widget position value
					ItemWidget->Position = Position;

					// Update Inventory array
					int InvIndex = InventoryComp->PosToIndex(Position);
					InventoryComp->Inventory[InvIndex] = FSlotData(ItemWidget->ItemData, false);

					// Reconstruct inventory UI
					InventoryWidget->ReconstructItems();
					ItemWidget->InventoryWidget->ReconstructItems();

					return true;
				}
			}
		}
	}
	return false;
}
