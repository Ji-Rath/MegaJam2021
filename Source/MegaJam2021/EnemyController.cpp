// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyController::AEnemyController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	// Bind perception update function to delegate
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::PerceptionUpdated);

	// Teams setup
	SetGenericTeamId(FGenericTeamId(TeamID));
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	const FAISenseID SenseID = Stimulus.Type;
	const FAISenseID SightID = UAISense::GetSenseID(UAISense_Sight::StaticClass());
	const FAISenseID HearingID = UAISense::GetSenseID(UAISense_Hearing::StaticClass());
	
	/** Sight stimulus */
	if (SenseID == SightID)
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			PlayerReference = Actor;
			SetState(Chasing);
			GetBlackboardComponent()->SetValueAsObject(BBPlayerReference, PlayerReference);

			// Clear timer that would cause the enemy to automatically search
			if (GetWorldTimerManager().IsTimerActive(ForgetTargetTimer))
			{
				GetWorldTimerManager().ClearTimer(ForgetTargetTimer);
			}
		}
		else
		{
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindUFunction(this, FName("SetState"), Searching);
			GetWorldTimerManager().SetTimer(ForgetTargetTimer, TimerDelegate, ForgetTargetTime, false);
		}
	}

	/** Hearing stimulus */
	if (SenseID == HearingID)
	{
		if (EnemyState == Idle || EnemyState == Searching)
		{
			/** Investigate stimulus location if not chasing the player already */
			SetState(Searching);
			GetBlackboardComponent()->SetValueAsVector(BBDestination, Stimulus.StimulusLocation);
			GetBlackboardComponent()->SetValueAsVector(BBSearchLocation, Stimulus.StimulusLocation);
		}
	}
}

void AEnemyController::SetState(EEnemyState NewState)
{
	EnemyState = NewState;
	GetBlackboardComponent()->SetValueAsEnum(BBEnemyState, (uint8) EnemyState);

	// Update search location
	if (NewState == Searching && PlayerReference)
	{
		GetBlackboardComponent()->SetValueAsVector(BBSearchLocation, PlayerReference->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(BBDestination, PlayerReference->GetActorLocation());

		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("SetState"), Idle);
		GetWorldTimerManager().SetTimer(ForgetTargetTimer, TimerDelegate, StopSearchingTime, false);
	}

	OnStateUpdated.Broadcast(NewState);
}

UAIPerceptionComponent* AEnemyController::GetPerceptionComponent()
{
	return AIPerceptionComponent;
}

void AEnemyController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	Team = TeamID;
}

FGenericTeamId AEnemyController::GetGenericTeamId() const
{
	return Team;
}
