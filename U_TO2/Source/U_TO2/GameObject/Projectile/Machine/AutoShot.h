#pragma once

#include "CoreMinimal.h"
#include "Machine.h"

class U_TO2_API AutoShot : public Machine
{
public:
	AutoShot(UWorld* InputWorld, const EAttackType& InputAttackType);
	virtual ~AutoShot();

protected:
	virtual void CreateProjectile() override;

protected:
	const float CreateTime{ 0.5f };
};
