// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionTypes.h"
#include "Components/ActorComponent.h"
#include "PerceptionLogicComponent.generated.h"

class UAIPerceptionComponent;
class UBlackboardComponent;

UENUM()
enum EEnemyState
{
	Idle,
	Searching,
	Chasing
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateUpdated, EEnemyState, EnemyState);

/**
 * 
 */
UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class MEGAJAM2021_API UPerceptionLogicComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:

	void BeginPlay() override;

	/** Called whenever AI Perception receives a stimulus */
	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void HearingUpdated(AActor* Actor, FAIStimulus& Stimulus);

	UFUNCTION()
	void SightUpdated(FAIStimulus& Stimulus, AActor* Actor);

	ETeamAttitude::Type GetAttitudeTowards(AActor* Actor);

	/** The current state of the enemy */
	UPROPERTY(VisibleAnywhere, Category = "AI")
	TEnumAsByte<EEnemyState> EnemyState;

	/** String reference to BB Vector. Intended to guide AI to stimulus */
	UPROPERTY(EditDefaultsOnly, Category = "AI|Blackboard")
	FName BBDestination;

	/** String reference to BB Vector. Intended for searching an area */
	UPROPERTY(EditDefaultsOnly, Category = "AI|Blackboard")
	FName BBSearchLocation;

	/** String reference to BB enum. Used to manage AI state */
	UPROPERTY(EditDefaultsOnly, Category = "AI|Blackboard")
	FName BBEnemyState;

	/** String reference to BB enum. Used to manage AI state */
	UPROPERTY(EditDefaultsOnly, Category = "AI|Blackboard")
	FName BBPlayerReference;

	/** Update the state of the enemy */
	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetState(EEnemyState NewState);

	/** Time it takes to 'lose' the target and begin searching */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float ForgetTargetTime = 5.f;

	/** Time it takes for the enemy to give up on searching for the player */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float StopSearchingTime = 10.f;

	/** Range that will alert nearby AI of the players presence */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float CallBackupRange = 1000.f;

	UAIPerceptionComponent* GetPerceptionComponent();

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent = nullptr;

	UPROPERTY()
	UBlackboardComponent* BlackboardComponent = nullptr;

	UPROPERTY(BlueprintAssignable)
	FStateUpdated OnStateUpdated;

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	AActor* PlayerReference;

	UPROPERTY()
	FTimerHandle ForgetTargetTimer;

	UBlackboardComponent* GetBlackboardComponent();
};
