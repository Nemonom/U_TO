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

void Machine::CreateProjectile()
{
}
