// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "EnemyObject.h"

EnemyManager::EnemyManager(UWorld* InputWorld, FVector FActorLocation) : World(InputWorld), ActorLocation(FActorLocation)
{
	// ���� ����
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
		//  AMyActor* pActor = GetWorld()->SpawnActorDeferred<AMyActor>(MyActorTemplate, GetActorLocation(), SpawnRotation); 
		NewEnemy->Init(EObjType::ENEMY);
		NewEnemy->SetPos(ActorLocation);
		Enemys.Add(NewEnemy);
	}
}
