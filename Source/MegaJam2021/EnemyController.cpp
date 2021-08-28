// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"

AEnemyController::AEnemyController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

void AEnemyController::BeginPlay()
{
	// Bind perception update function to delegate
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::PerceptionUpdated);
}

void AEnemyController::Tick(float DeltaTime)
{

}

void AEnemyController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{

}
