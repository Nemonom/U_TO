#pragma once

#include "CoreMinimal.h"
#include "../../../Common/U_TOCommon.h"

class U_TO2_API Machine
{
public:
	Machine();
	Machine(UWorld* InputWorld, const EAttackType& InputAttackType);
	virtual ~Machine();

	virtual void Tick(float DeltaTime);
	
	void SetPos(const FVector& Pos);
	void SetDir(const FVector& Dir);

protected:
	virtual void CreateProjectile();

protected:
	UWorld* World{ nullptr };

	TArray<TWeakObjectPtr<class AProjectileObject>> ProjectileArray;
	FVector BasePos{ FVector(0, 0, 0) };
	FVector CustomDir{ FVector(0, 0, 0) };
	EAttackType AttackType{ EAttackType::ENEMY };

	FTimerHandle ProjectileTimerHandle = { };
};
