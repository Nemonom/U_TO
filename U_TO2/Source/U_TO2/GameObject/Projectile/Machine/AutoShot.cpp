#include "AutoShot.h"
#include "../ProjectileObject.h"

AutoShot::AutoShot(UWorld* InputWorld) : Machine(InputWorld)
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

AutoShot::~AutoShot()
{
}

void AutoShot::CreateProjectile()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AProjectileObject* NewProjectile = World->SpawnActor<AProjectileObject>(AProjectileObject::StaticClass(), BasePos, FRotator::ZeroRotator, SpawnInfo);
	if (NewProjectile)
	{
		//FVector dir = player - this;
		FVector dir;
		NewProjectile->FireInDirection(dir.GetSafeNormal());
		ProjectileArray.Add(NewProjectile);
	}
}