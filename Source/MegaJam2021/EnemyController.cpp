#include "EnemyController.h"



void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
	// Teams setup
	SetGenericTeamId(FGenericTeamId(TeamID));
}


void AEnemyController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	Team = NewTeamID;
}

FGenericTeamId AEnemyController::GetGenericTeamId() const
{
	return Team;
}