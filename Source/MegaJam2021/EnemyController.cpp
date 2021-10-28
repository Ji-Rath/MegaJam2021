#include "EnemyController.h"



AEnemyController::AEnemyController()
{
	// Teams setup
	SetGenericTeamId(FGenericTeamId(TeamID));
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
}