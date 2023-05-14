// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLevel.h"
#include "../../U_TO2/GameObject/Enemy/EnemyManager.h"

void AGameLevel::BeginPlay()
{
	Super::BeginPlay();
	EnemyManager_ = new EnemyManager();
}

void AGameLevel::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	EnemyManager_ = nullptr;
}
