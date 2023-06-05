// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "EnemyObject.h"

EnemyManager::EnemyManager(UWorld* InputWorld, FVector FActorLocation) : World(InputWorld), ActorLocation(FActorLocation)
{
	// ���� ����
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//AEnemyObject* NewEnemy = World->SpawnActor<AEnemyObject>(AEnemyObject::StaticClass(), SpawnInfo);
	//TSharedPtr<AEnemyObject> Enemy = MakeShareable(NewEnemy);
	//Enemy->Init(EObjType::BOSS);
	//Enemy->SetPos(ActorLocation);
	//Enemys.Add(Enemy);

	TSharedPtr<AEnemyObject> NewEnemy = MakeShareable(NewObject<AEnemyObject>());
	NewEnemy->Init(EObjType::BOSS); 
	NewEnemy->SetPos(ActorLocation);
	Enemys.Add(NewEnemy);

	World->GetTimerManager().SetTimer(MyTimerHandle, FTimerDelegate::CreateLambda([this]() -> void
		{
			CreateEnemy();
		}	
	), CreateEnemyTime, true, 10.f);
}

EnemyManager::~EnemyManager()
{
	World->GetTimerManager().ClearTimer(MyTimerHandle);
	Enemys.Empty();
}

void EnemyManager::CreateEnemy()
{
	for (int i = 0; i < CreateEnemyNum; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEnemyObject* NewEnemy = World->SpawnActor<AEnemyObject>(AEnemyObject::StaticClass(), SpawnInfo);
		TSharedPtr<AEnemyObject> Enemy = MakeShareable(NewEnemy);
		Enemy->Init(EObjType::ENEMY);
		Enemy->SetPos(ActorLocation);
		Enemys.Add(Enemy);
	}
}
