#include "WaveMachine.h"
#include "../ProjectileObject.h"

WaveMachine::WaveMachine(UWorld* InputWorld) : Machine(InputWorld)
{
	if (World)
	{
		World->GetTimerManager().SetTimer(ProjectileTimerHandle, FTimerDelegate::CreateLambda([this]() -> void
			{
				CreateProjectile();
			}
		), CreateTime, true, 5.f);
	}
}

WaveMachine::~WaveMachine()
{
	ProjectileArray.Empty();
}

void WaveMachine::CreateProjectile()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int i = 0; i < 5; i++)
	{
		AProjectileObject* NewProjectile = World->SpawnActor<AProjectileObject>(AProjectileObject::StaticClass(), BasePos, FRotator::ZeroRotator, SpawnInfo);
		if (NewProjectile)
		{
			FVector dir{ (rand() % 10 - 5) * 1.f, (rand() % 10 - 5) * 1.f, (rand() % 10 - 5) * 1.f };
			NewProjectile->FireInDirection(dir.GetSafeNormal());
			ProjectileArray.Add(NewProjectile);
		}
	}
}
