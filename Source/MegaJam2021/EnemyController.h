#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

UCLASS()
class MEGAJAM2021_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Team")
	uint8 TeamID = FGenericTeamId::NoTeam;

protected:
	void BeginPlay() override;

private:
	void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

	FGenericTeamId GetGenericTeamId() const override;

	FGenericTeamId Team;
};


