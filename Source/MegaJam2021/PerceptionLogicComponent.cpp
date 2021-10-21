// Fill out your copyright notice in the Description page of Project Settings.


#include "PerceptionLogicComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "BehaviorTree/BlackboardComponent.h"


void UPerceptionLogicComponent::BeginPlay()
{
	Super::BeginPlay();

	/* Get AIPerception component */
	AIPerceptionComponent = GetOwner()->FindComponentByClass<UAIPerceptionComponent>();
	if (ensure(AIPerceptionComponent))
	{
		// Bind perception update function to delegate
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &UPerceptionLogicComponent::PerceptionUpdated);
	}

	/* Get blackboard component */
	BlackboardComponent = GetOwner()->FindComponentByClass<UBlackboardComponent>();
	ensure(BlackboardComponent);
}

void UPerceptionLogicComponent::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	const FAISenseID SenseID = Stimulus.Type;
	const FAISenseID SightID = UAISense::GetSenseID(UAISense_Sight::StaticClass());
	const FAISenseID HearingID = UAISense::GetSenseID(UAISense_Hearing::StaticClass());
	
	/** Sight stimulus */
	if (SenseID == SightID)
	{
		SightUpdated(Stimulus, Actor);
	}

	/** Hearing stimulus */
	if (SenseID == HearingID)
	{
		HearingUpdated(Stimulus);
	}
}

void UPerceptionLogicComponent::HearingUpdated(FAIStimulus& Stimulus)
{
	if (!BlackboardComponent) { return; }

	if (EnemyState == Idle || EnemyState == Searching)
	{
		/** Investigate stimulus location if not chasing the player already */
		SetState(Searching);
		GetBlackboardComponent()->SetValueAsVector(BBDestination, Stimulus.StimulusLocation);
		GetBlackboardComponent()->SetValueAsVector(BBSearchLocation, Stimulus.StimulusLocation);
	}
}

void UPerceptionLogicComponent::SightUpdated(FAIStimulus& Stimulus, AActor* Actor)
{
	if (!BlackboardComponent) { return; }

	if (Stimulus.WasSuccessfullySensed())
	{
		PlayerReference = Actor;
		SetState(Chasing);
		GetBlackboardComponent()->SetValueAsObject(BBPlayerReference, PlayerReference);

		// Clear timer that would cause the enemy to automatically search
		if (GetWorld()->GetTimerManager().IsTimerActive(ForgetTargetTimer))
		{
			GetWorld()->GetTimerManager().ClearTimer(ForgetTargetTimer);
		}
	}
	else
	{
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("SetState"), Searching);
		GetWorld()->GetTimerManager().SetTimer(ForgetTargetTimer, TimerDelegate, ForgetTargetTime, false);
	}
}

void UPerceptionLogicComponent::SetState(EEnemyState NewState)
{
	if (!BlackboardComponent) { return; }

	EnemyState = NewState;
	GetBlackboardComponent()->SetValueAsEnum(BBEnemyState, (uint8) EnemyState);

	// Update search location
	if (NewState == Searching && PlayerReference && ensure(GetBlackboardComponent()))
	{
		GetBlackboardComponent()->SetValueAsVector(BBSearchLocation, PlayerReference->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(BBDestination, PlayerReference->GetActorLocation());

		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("SetState"), Idle);
		GetWorld()->GetTimerManager().SetTimer(ForgetTargetTimer, TimerDelegate, StopSearchingTime, false);
	}

	OnStateUpdated.Broadcast(NewState);
}

UAIPerceptionComponent* UPerceptionLogicComponent::GetPerceptionComponent()
{
	return AIPerceptionComponent;
}

void UPerceptionLogicComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

UBlackboardComponent* UPerceptionLogicComponent::GetBlackboardComponent()
{
	return BlackboardComponent;
}
