// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "EnemyObject.h"

EnemyManager::EnemyManager(UWorld* InputWorld) : World(InputWorld)
{
	// 焊胶 积己
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Tick(float DeltaTime)
{
	Timer += DeltaTime;

	if (Timer >= CreateEnemyTimer)
	{
		CreateEnemy(3);
		Timer = 0;
	}
}

void EnemyManager::CreateEnemy(int cnt)
{
	for (int i = 0; i < cnt; ++i)
	{
		AEnemyObject* NewEnemy = World->SpawnActor<AEnemyObject>(AEnemyObject::StaticClass());
		TSharedPtr<AEnemyObject> Enemy = MakeShareable(NewEnemy); // TSharedPtr 积己
		Enemys.Add(Enemy);

	/*	AEnemyObject* NewEnemy2 = NewObject<AEnemyObject>();
		test.Add(NewEnemy2);*/

	}
}
