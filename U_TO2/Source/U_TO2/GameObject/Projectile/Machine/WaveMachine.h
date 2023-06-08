#pragma once

#include "CoreMinimal.h"
#include "Machine.h"


class U_TO2_API WaveMachine : public Machine
{
public:
	WaveMachine(UWorld* InputWorld, const EAttackType& InputAttackType);
	virtual ~WaveMachine();

protected:
	virtual void CreateProjectile() override;

protected:
	const float CreateTime{ 1.5f };
};
