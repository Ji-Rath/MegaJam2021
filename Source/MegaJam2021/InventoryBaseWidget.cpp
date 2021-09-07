// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryBaseWidget.h"
#include "Components/GridPanel.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "ItemData.h"
#include "Kismet/GameplayStatics.h"
#include "InventoryComponent.h"
#include "ItemBaseWidget.h"
#include "TileBaseWidget.h"

void UInventoryBaseWidget::ConstructGrid(FIntVector2D Size)
{
	for (int i = 0; i < Size.X; i++)
	{
		for (int j = 0; j < Size.Y; j++)
		{
			UTileBaseWidget* Tile = CreateWidget<UTileBaseWidget>(GetOwningPlayer(), SlotWidget);
			GridTiles->AddChildToGrid(Tile, j, i);
			if (Tile)
			{
				Tile->InventoryWidget = this;
				Tile->Position = FIntVector2D(i, j);
			}
		}
	}
}

void UInventoryBaseWidget::AddItem(UItemData* ItemData, FIntVector2D Position)
{
	UItemBaseWidget* Item = CreateWidget<UItemBaseWidget>(GetOwningPlayer(), ItemWidget);
	UCanvasPanelSlot* CanvasItem = CanvasItems->AddChildToCanvas(Item);
	CanvasItem->SetAutoSize(true);
	CanvasItem->SetPosition(FVector2D(Position.X,Position.Y)*100);
	Item->Position = Position;
	Item->ItemData = ItemData;
	Item->InventoryWidget = this;
	Item->Initialize();
}

void UInventoryBaseWidget::ToggleInventory(bool bOpen)
{
	EUMGSequencePlayMode::Type PlayMode = bOpen ? EUMGSequencePlayMode::Forward : EUMGSequencePlayMode::Reverse;
	PlayAnimation(FadeInAnim, 0.0f, 1, PlayMode);
	if (GetOwningPlayer())
	{
		GetOwningPlayer()->SetIgnoreLookInput(true);
		GetOwningPlayer()->bShowMouseCursor = true;
	}

	if (bOpen)
	{
		ReconstructItems();
	}
}

void UInventoryBaseWidget::ReconstructItems()
{
	CanvasItems->ClearChildren();
	for(int i = 0; i < InventoryReference->Inventory.Num(); i++)
	{
		FSlotData SlotData = InventoryReference->Inventory[i];
		if (SlotData.Item != nullptr)
		{
			FIntVector2D Position = InventoryReference->IndexToPos(i);
			AddItem(SlotData.Item, Position);
		}
	}
}

bool UInventoryBaseWidget::Initialize()
{
	bool bSuccess = Super::Initialize();
	
	AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ActorTarget);
	if (Actor)
	{
		InventoryReference = Actor->FindComponentByClass<UInventoryComponent>();
		if (InventoryReference)
		{
			InventoryReference->OnItemAdded.AddDynamic(this, &UInventoryBaseWidget::AddItem);
			ConstructGrid(InventoryReference->InventorySize);
			InventoryReference->OnToggleInventory.AddDynamic(this, &UInventoryBaseWidget::ToggleInventory);
		}
	}

	return bSuccess;
}

UInventoryBaseWidget::UInventoryBaseWidget(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	ConstructGrid(FIntVector2D(3, 3));
}
