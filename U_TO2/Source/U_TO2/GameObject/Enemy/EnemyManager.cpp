// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "EnemyObject.h"

EnemyManager::EnemyManager(UWorld* InputWorld) : World(InputWorld)
{
	// 보스 생성
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEnemyObject* NewEnemy = World->SpawnActor<AEnemyObject>(AEnemyObject::StaticClass(), SpawnInfo);
	TSharedPtr<AEnemyObject> Enemy = MakeShareable(NewEnemy);
	Enemy->Init(EObjType::BOSS);
	Enemys.Add(Enemy);
}

EnemyManager::~EnemyManager()
{
	Enemys.Empty();
}

void EnemyManager::Tick(float DeltaTime)
{
	Timer += DeltaTime;

	if (Timer >= CreateEnemyTimer)
	{
		//CreateEnemy(3);
		Timer = 0;
	}
}

void EnemyManager::CreateEnemy(int cnt)
{
	for (int i = 0; i < cnt; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEnemyObject* NewEnemy = World->SpawnActor<AEnemyObject>(AEnemyObject::StaticClass(), SpawnInfo);
		TSharedPtr<AEnemyObject> Enemy = MakeShareable(NewEnemy);
		Enemy->Init(EObjType::ENEMY);
		Enemys.Add(Enemy);
	}
}
