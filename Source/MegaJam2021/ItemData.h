// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FIntVector2D
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int X = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Y = 1;

	FIntVector2D()
	{
		X = 1;
		Y = 1;
	};

	FIntVector2D(int XVal, int YVal)
	{
		X = XVal;
		Y = YVal;
	};
};

USTRUCT(BlueprintType)
struct FSlotData
{
	GENERATED_USTRUCT_BODY()

	/** Store a reference of the item data when this is the primary slot */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UItemData* Item = nullptr;

	/** Used when Item is nullptr but the space is still taken */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bTaken = false;

	FSlotData()
	{
		Item = nullptr;

		bTaken = false;
	};

	FSlotData(UItemData* NewItem, bool bIsTaken)
	{
		Item = NewItem;
		bTaken = bIsTaken;
	};
};

/**
 * 
 */
UCLASS(BlueprintType)
class MEGAJAM2021_API UItemData : public UDataAsset
{
	GENERATED_BODY()

public:

	/** Texture of item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* ItemIcon = nullptr;

	/** Size that the item takes up in inventory */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FIntVector2D Size = FIntVector2D();

	/** The value of the item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ItemValue = 0.f;

	/** Name of the item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name = FText::FromString(TEXT("NoName"));

	/** Description of item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

};
