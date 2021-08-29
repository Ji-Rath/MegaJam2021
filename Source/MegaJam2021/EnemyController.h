// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyController.generated.h"

class UAIPerceptionComponent;

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
UCLASS()
class MEGAJAM2021_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyController();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	/** Called whenever AI Perception receives a stimulus */
	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

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

	UAIPerceptionComponent* GetPerceptionComponent() override;

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(BlueprintAssignable)
	FStateUpdated OnStateUpdated;

	UPROPERTY(EditDefaultsOnly, Category = "Team")
	uint8 TeamID = FGenericTeamId::NoTeam;

private:
	UPROPERTY()
	AActor* PlayerReference;

	UPROPERTY()
	FTimerHandle ForgetTargetTimer;

	void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

	FGenericTeamId GetGenericTeamId() const override;

	FGenericTeamId Team;

};
