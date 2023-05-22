// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Common/U_TOCommon.h"

class U_TO2_API EnemyManager
{
public:
	EnemyManager(UWorld* InputWorld);
	~EnemyManager();

	void Tick(float DeltaTime);

	void CreateEnemy(int cnt);

private:
	TArray<TSharedPtr<class AEnemyObject>> Enemys;
	float Timer{ 0.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		int CreateEnemyTimer{ 30 };

	UWorld* World{ nullptr };
};