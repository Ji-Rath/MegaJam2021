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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UItemData* Item = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSourceTile = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bTaken = false;
};

/**
 * 
 */
UCLASS(BlueprintType)
class MEGAJAM2021_API UItemData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* ItemIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FIntVector2D Size;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ItemValue = 0.f;
};
