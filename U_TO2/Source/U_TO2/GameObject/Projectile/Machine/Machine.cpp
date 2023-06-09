#include "Machine.h"

Machine::Machine()
{
}

Machine::Machine(UWorld* InputWorld, const EAttackType& InputAttackType)
{
	World = InputWorld;
	AttackType = InputAttackType;
}

Machine::~Machine()
{
	ProjectileArray.Empty();
	World = nullptr;
}

void Machine::Tick(float DeltaTime)
{
}

void Machine::SetPos(const FVector& Pos)
{
	BasePos = Pos;
}

void Machine::SetDir(const FVector& Dir)
{
	CustomDir = Dir;
}

void Machine::OnMasterDie()
{
	if (World)
		World->GetTimerManager().ClearTimer(ProjectileTimerHandle);
}


void Machine::CreateProjectile()
{
}
