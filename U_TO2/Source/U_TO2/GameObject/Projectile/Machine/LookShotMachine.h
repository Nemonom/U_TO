#pragma once

#include "CoreMinimal.h"
#include "Machine.h"

class U_TO2_API LookShotMachine	: public Machine
{
public:
	LookShotMachine(UWorld* InputWorld, const EAttackType& InputAttackType);
	virtual ~LookShotMachine();

protected:
	virtual void CreateProjectile() override;

protected:
	const float CreateTime{ 0.5f };
};
