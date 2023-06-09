// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "EnemyObject.h"

EnemyManager::EnemyManager(UWorld* InputWorld, FVector FActorLocation) : World(InputWorld), ActorLocation(FActorLocation)
{
	// ���� ����
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform transform;
	transform.SetTranslation(FVector::ZeroVector);
	transform.SetRotation(FRotator::ZeroRotator.Quaternion());

	AEnemyObject* NewEnemy = World->SpawnActorDeferred<AEnemyObject>(AEnemyObject::StaticClass(), transform);
	if (NewEnemy)
	{
		NewEnemy->Init(EObjType::BOSS);
		NewEnemy->SetPos(ActorLocation);
		Enemys.Add(NewEnemy);

		UGameplayStatics::FinishSpawningActor(NewEnemy, transform);
	}

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

		FTransform transform;
		transform.SetTranslation(FVector::ZeroVector);
		transform.SetRotation(FRotator::ZeroRotator.Quaternion());

		AEnemyObject* NewEnemy = World->SpawnActorDeferred<AEnemyObject>(AEnemyObject::StaticClass(), transform);
		if (NewEnemy)
		{
			NewEnemy->Init(EObjType::ENEMY);
			NewEnemy->SetPos(ActorLocation);
			Enemys.Add(NewEnemy);

			UGameplayStatics::FinishSpawningActor(NewEnemy, transform);
		}
	}
}
