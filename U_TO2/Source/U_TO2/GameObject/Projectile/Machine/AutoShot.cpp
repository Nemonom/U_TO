#include "AutoShot.h"
#include "../ProjectileObject.h"
#include "../../Player/PlayerObject.h"

AutoShot::AutoShot(UWorld* InputWorld, const EAttackType& InputAttackType) : Machine(InputWorld, InputAttackType)
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

	FTransform transform;
	transform.SetTranslation(BasePos);
	transform.SetRotation(FRotator::ZeroRotator.Quaternion());

	AProjectileObject* NewProjectile = World->SpawnActorDeferred<AProjectileObject>(AProjectileObject::StaticClass(), transform);
	if (NewProjectile)
	{
		for (TActorIterator<APlayerObject> It(World); It; ++It)
		{
			APlayerObject* PlayerObj = *It;
			FVector dir{ (rand() % 10 - 5) * 1.f, (rand() % 10 - 5) * 1.f, (rand() % 10 - 5) * 1.f };
			NewProjectile->Init(AttackType);
			NewProjectile->SetScale(FVector(0.4f, 0.4f, 0.4f));
			NewProjectile->FireInDirection(dir.GetSafeNormal());
			ProjectileArray.Add(NewProjectile);
		}

		UGameplayStatics::FinishSpawningActor(NewProjectile, transform);
	}
}