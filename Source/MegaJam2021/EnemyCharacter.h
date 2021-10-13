#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class MEGAJAM2021_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	

	void BeginPlay() override;

	UFUNCTION()
	void ActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};

