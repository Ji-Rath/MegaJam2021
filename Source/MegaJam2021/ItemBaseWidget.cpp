// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBaseWidget.h"
#include "ItemData.h"
#include "Components/GridPanel.h"

UItemBaseWidget::UItemBaseWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructGrid(FIntVector2D(3, 3));
}

void UItemBaseWidget::ConstructGrid(FIntVector2D Size)
{
	for (int i = 0; i < Size.X; i++)
	{
		for (int j = 0; j < Size.Y; j++)
		{
			auto* Tile = CreateWidget(GetOwningPlayer(), SlotWidget);
			GridTiles->AddChildToGrid(Tile, j, i);
		}
	}
}
