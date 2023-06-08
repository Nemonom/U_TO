#include "AutoShot.h"
#include "../ProjectileObject.h"
#include "../../Player/PlayerObject.h"

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
	if (nullptr == World)
		return;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AProjectileObject* NewProjectile = World->SpawnActor<AProjectileObject>(AProjectileObject::StaticClass(), BasePos, FRotator::ZeroRotator, SpawnInfo);
	if (NewProjectile)
	{
		for (TActorIterator<APlayerObject> It(World); It; ++It)
		{
			APlayerObject* PlayerObj = *It;
			FVector dir = PlayerObj->GetActorLocation() - BasePos;
			NewProjectile->SetScale(FVector(0.2f, 0.2f, 0.2f));
			NewProjectile->FireInDirection(dir.GetSafeNormal());
			ProjectileArray.Add(NewProjectile);
		}
	}
}