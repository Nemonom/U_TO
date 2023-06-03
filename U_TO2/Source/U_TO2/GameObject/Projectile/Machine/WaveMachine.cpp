#include "WaveMachine.h"
#include "../ProjectileObject.h"

WaveMachine::WaveMachine()
{
}

WaveMachine::~WaveMachine()
{
	ProjectileArray.Empty();
}

void WaveMachine::Tick(float DeltaTime)
{
	m_Ctime += DeltaTime;

	if (m_Ctime > m_Maxtime)
	{
		m_Ctime = 0;


		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		for (int i = 0; i < 5; i++)
		{
			AProjectileObject* NewProjectile = World->SpawnActor<AProjectileObject>(AProjectileObject::StaticClass(), BasePos, FRotator::ZeroRotator, SpawnInfo);
			if (NewProjectile)
			{
				FVector dir{ (rand() % 10 - 5) * 1.f, (rand() % 10 - 5) * 1.f, (rand() % 10 - 5) * 1.f };
				NewProjectile->FireInDirection(dir.GetSafeNormal());
				ProjectileArray.Add(NewProjectile);
			}
		}
	}
}
