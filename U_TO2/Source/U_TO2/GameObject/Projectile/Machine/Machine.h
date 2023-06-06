#pragma once

#include "CoreMinimal.h"

class U_TO2_API Machine
{
public:
	Machine();
	Machine(UWorld* InputWorld);
	~Machine();

	virtual void Tick(float DeltaTime);
	
	void SetPos(const FVector& Pos);

protected:
	virtual void CreateProjectile();

protected:
	UWorld* World{ nullptr };

	TArray<TWeakObjectPtr<class AProjectileObject>> ProjectileArray;
	FVector BasePos{ FVector(0, 0, 0) };

	FTimerHandle ProjectileTimerHandle = { };
};
