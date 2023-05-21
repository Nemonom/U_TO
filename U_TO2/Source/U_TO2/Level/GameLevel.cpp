// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLevel.h"
#include "../../U_TO2/GameObject/Enemy/EnemyManager.h"

void AGameLevel::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = true;

	Super::BeginPlay();
	EnemyManager_ = new EnemyManager(GetWorld());
}

void AGameLevel::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	EnemyManager_ = nullptr;
}

void AGameLevel::Tick(float DeltaTime)
{
	EnemyManager_->Tick(DeltaTime);

	Super::Tick(DeltaTime);
}