// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class MEGAJAM2021_API APlayerCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditDefaultsOnly, Category = "Team")
	uint8 TeamID = FGenericTeamId::NoTeam;

	void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

	FGenericTeamId GetGenericTeamId() const override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FGenericTeamId Team;

};
