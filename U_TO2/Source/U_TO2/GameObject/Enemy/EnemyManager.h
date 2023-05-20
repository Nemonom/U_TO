// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class U_TO2_API EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void Tick(float DeltaTime);

	void CreateEnemy();

private:
	TArray<TSharedRef<class UEnemyObject>> Enemys;
	float Timer{ 0.f };
};