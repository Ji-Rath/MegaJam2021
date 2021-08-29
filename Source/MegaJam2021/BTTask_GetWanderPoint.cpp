// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetWanderPoint.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_GetWanderPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AActor* Owner = OwnerComp.GetOwner();

	if (Blackboard)
	{
		// Get wander point
		FNavLocation NavLocation;
		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
		NavSystem->GetRandomReachablePointInRadius(Owner->GetActorLocation(), Radius, OUT NavLocation);

		FVector Destination = NavLocation.Location;

		// Update blackboard value
		Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), Destination);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
