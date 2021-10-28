// Fill out your copyright notice in the Description page of Project Settings.


#include "PerceptionLogicComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISense_Team.h"
#include "GenericTeamAgentInterface.h"
#include "MissingItem.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"


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
	const FAISenseID TeamSenseID = UAISense::GetSenseID(UAISense_Team::StaticClass());
	
	/** Sight stimulus */
	if (SenseID == SightID)
	{
		SightUpdated(Stimulus, Actor);
	}

	/** Hearing stimulus */
	if (SenseID == HearingID)
	{
		HearingUpdated(Actor, Stimulus);
	}

	/* Team sense stimulus (Same as hearing stimulus) */
	if (SenseID == TeamSenseID)
	{
		HearingUpdated(Actor, Stimulus);
	}
}

void UPerceptionLogicComponent::HearingUpdated(AActor* Actor, FAIStimulus& Stimulus)
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

	ETeamAttitude::Type Attitude = GetAttitudeTowards(Actor);

	/* Hostile detected */
	if (Attitude == ETeamAttitude::Hostile)
	{
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

			/* Alert nearby AI that player was found */
			UAIPerceptionSystem* PerceptionSystem = UAIPerceptionSystem::GetCurrent(GetWorld());
			if (PerceptionSystem)
			{
				FAITeamStimulusEvent TeamStimEvent(GetOwner(), Actor, Actor->GetActorLocation(), CallBackupRange);
				PerceptionSystem->OnEvent(TeamStimEvent);
			}
		}
		else
		{
			/* If the stimulus was 'lost', set a timer to begin searching */
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindUFunction(this, FName("SetState"), Searching);
			GetWorld()->GetTimerManager().SetTimer(ForgetTargetTimer, TimerDelegate, ForgetTargetTime, false);
		}
	}

	/* Neutral actor detected */
	if (Attitude == ETeamAttitude::Neutral)
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			/* If an item has gone missing, search the area and destroy missing item (using hearing logic) */
			if (Cast<AMissingItem>(Actor))
			{
				HearingUpdated(Actor, Stimulus);
			}
		}
		else
		{
			Actor->Destroy();
			Stimulus.MarkNoLongerSensed();
		}
	}
}

ETeamAttitude::Type UPerceptionLogicComponent::GetAttitudeTowards(AActor* Actor)
{
	/* Determine AI attitude of sensed actor */
	ETeamAttitude::Type Attitude = ETeamAttitude::Neutral;
	if (AController* Owner = GetOwner<AController>())
	{
		auto* TeamInterface = Cast<IGenericTeamAgentInterface>(Owner);
		if (TeamInterface)
		{
			Attitude = TeamInterface->GetTeamAttitudeTowards(*Actor);
		}
	}

	return Attitude;
}

void UPerceptionLogicComponent::SetState(EEnemyState NewState)
{
	if (!BlackboardComponent) { return; }

	EnemyState = NewState;
	GetBlackboardComponent()->SetValueAsEnum(BBEnemyState, (uint8) EnemyState);

	if (NewState == Searching)
	{
		/* Update search location to be on player (kinda cheating) */
		if (PlayerReference)
		{
			GetBlackboardComponent()->SetValueAsVector(BBSearchLocation, PlayerReference->GetActorLocation());
			GetBlackboardComponent()->SetValueAsVector(BBDestination, PlayerReference->GetActorLocation());
		}
		
		/* Give up searching after set time */
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("SetState"), Idle);
		GetWorld()->GetTimerManager().SetTimer(ForgetTargetTimer, TimerDelegate, StopSearchingTime, false);

		/**
		 * Gradually increase search time
		 * @todo Give BP's edit access to hard coded values
		 */
		StopSearchingTime = FMath::Clamp<float>(StopSearchingTime + 5.f, 0, 30.f);
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
