// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetNextSplinePoint.generated.h"

/**
 * 
 */
UCLASS()
class MEGAJAM2021_API UBTTask_GetNextSplinePoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	

public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector CurrentIndex;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector SplinePointLocation;

};
