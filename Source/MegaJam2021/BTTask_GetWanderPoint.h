// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetWanderPoint.generated.h"

/**
 * 
 */
UCLASS()
class MEGAJAM2021_API UBTTask_GetWanderPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	float Radius = 500.f;

};
