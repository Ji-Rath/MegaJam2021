// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetNextSplinePoint.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_GetNextSplinePoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard)
	{
		AActor* SplineActor = Cast<AActor>(Blackboard->GetValueAsObject(GetSelectedBlackboardKey()));
		int32 SplineIndex = Blackboard->GetValueAsInt(CurrentIndex.SelectedKeyName);

		if (SplineActor)
		{
			USplineComponent* Spline = SplineActor->FindComponentByClass<USplineComponent>();
			if (Spline)
			{
				// Get spline location
				const int32 SplinePoints = Spline->GetNumberOfSplinePoints();
				const FVector PointLocation = Spline->GetLocationAtSplinePoint(SplineIndex, ESplineCoordinateSpace::World);

				// Increment index
				if (SplineIndex < SplinePoints)
				{
					SplineIndex++;
				}
				else
				{
					SplineIndex = 0;
				}

				// Update blackboard index and destination
				Blackboard->SetValueAsInt(CurrentIndex.SelectedKeyName, SplineIndex);
				Blackboard->SetValueAsVector(SplinePointLocation.SelectedKeyName, PointLocation);

				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
