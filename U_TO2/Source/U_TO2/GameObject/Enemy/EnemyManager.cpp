// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "EnemyObject.h"

EnemyManager::EnemyManager(UWorld* InputWorld, FVector FActorLocation) : World(InputWorld), ActorLocation(FActorLocation)
{
	// 보스 생성
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEnemyObject* Enemy = World->SpawnActor<AEnemyObject>(AEnemyObject::StaticClass(), SpawnInfo);
	Enemy->Init(EObjType::BOSS);
	Enemy->SetPos(ActorLocation);
	Enemys.Add(Enemy);

	World->GetTimerManager().SetTimer(MyTimerHandle, FTimerDelegate::CreateLambda([this]() -> void
		{
			CreateEnemy();
		}	
	), CreateEnemyTime, true, 10.f);
}

EnemyManager::~EnemyManager()
{
	Enemys.Empty();

	World->GetTimerManager().ClearTimer(MyTimerHandle);
}

AEnemyObject* EnemyManager::GetBoss()
{
	for (const auto& Enemy : Enemys)
	{
		if (Enemy->GetObjType() == EObjType::BOSS)
			return Enemy;
	}

	return nullptr;
}

void EnemyManager::KillAllEnemy()
{
	for (const auto& Enemy : Enemys)
	{
		Enemy->Die();
	}
}

void EnemyManager::CreateEnemy()
{
	for (int i = 0; i < CreateEnemyNum; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEnemyObject* NewEnemy = World->SpawnActor<AEnemyObject>(AEnemyObject::StaticClass(), SpawnInfo);
		//  AMyActor* pActor = GetWorld()->SpawnActorDeferred<AMyActor>(MyActorTemplate, GetActorLocation(), SpawnRotation); 
		NewEnemy->Init(EObjType::ENEMY);
		NewEnemy->SetPos(ActorLocation);
		Enemys.Add(NewEnemy);
	}
}
