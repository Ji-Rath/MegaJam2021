#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class MEGAJAM2021_API AEnemyCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

	UPROPERTY(EditDefaultsOnly, Category = "Team")
	uint8 TeamID = FGenericTeamId::NoTeam;

	void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

	FGenericTeamId GetGenericTeamId() const override;

	void BeginPlay() override;

	UFUNCTION()
	void ActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

private:
	FGenericTeamId Team;
};

