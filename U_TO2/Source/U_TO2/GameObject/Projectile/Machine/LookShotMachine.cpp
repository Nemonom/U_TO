#include "LookShotMachine.h"
#include "../ProjectileObject.h"
#include "../../Player/PlayerObject.h"

LookShotMachine::LookShotMachine(UWorld* InputWorld, const EAttackType& InputAttackType) : Machine(InputWorld, InputAttackType)
{
	if (World)
	{
		World->GetTimerManager().SetTimer(ProjectileTimerHandle, FTimerDelegate::CreateLambda([this]() -> void
			{
				CreateProjectile();
			}
		), CreateTime, true, 3.f);
	}
}

LookShotMachine::~LookShotMachine()
{
}

void LookShotMachine::CreateProjectile()
{
	if (nullptr == World)
		return;

	FTransform transform;
	transform.SetTranslation(BasePos);
	transform.SetRotation(FRotator::ZeroRotator.Quaternion());

	AProjectileObject* NewProjectile = World->SpawnActorDeferred<AProjectileObject>(AProjectileObject::StaticClass(), transform);
	if (NewProjectile)
	{
		NewProjectile->Init(AttackType);
		NewProjectile->SetScale(FVector(0.2f, 0.2f, 0.2f));
		NewProjectile->FireInDirection(CustomDir.GetSafeNormal());
		ProjectileArray.Add(NewProjectile);

		UGameplayStatics::FinishSpawningActor(NewProjectile, transform);
	}
}