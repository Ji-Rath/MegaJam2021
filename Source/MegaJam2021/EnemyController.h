// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyController.generated.h"

class UAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class MEGAJAM2021_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyController();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
