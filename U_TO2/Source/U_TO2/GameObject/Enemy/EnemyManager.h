// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Common/U_TOCommon.h"

class U_TO2_API EnemyManager
{
public:
	EnemyManager(UWorld* InputWorld, FVector FActorLocation);
	~EnemyManager();

	class AEnemyObject* GetBoss();
	void KillAllEnemy();

private:
	void CreateEnemy();

private:
	UWorld* World{ nullptr };
	
	TArray<class AEnemyObject*> Enemys;

	FVector ActorLocation{ FVector::ZeroVector };
	float CreateEnemyTime{ 30.f };
	FTimerHandle MyTimerHandle = { };
	int CreateEnemyNum{ 3 };
};