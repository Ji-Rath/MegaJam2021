#include "EnemyCharacter.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Touch.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"



void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorHit.AddDynamic(this, &AEnemyCharacter::ActorHit);
}

void AEnemyCharacter::ActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UAIPerceptionSystem* PerceptionSystem = UAIPerceptionSystem::GetCurrent(GetWorld());
	if (PerceptionSystem)
	{
		FAITouchEvent Event(SelfActor, OtherActor, Hit.Location);
		PerceptionSystem->OnEvent(Event);

		FAINoiseEvent SightEvent(OtherActor, Hit.Location);
		PerceptionSystem->OnEvent(SightEvent);

		UE_LOG(LogTemp, Warning, TEXT("Sent touch event!"));
	}
}