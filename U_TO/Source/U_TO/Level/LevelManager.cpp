// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"

LevelManager* LevelManager::Instance = nullptr;

LevelManager::LevelManager()
{
	LevelInfos.Add(FName("Game"));
	LevelInfos.Add(FName("Help"));
}

LevelManager::~LevelManager()
{
}

LevelManager* LevelManager::GetInstance()
{
	if (nullptr == Instance) {
		Instance = new LevelManager();
	}
	return Instance;
}

FName LevelManager::GetLevelInfo(int LevelIndex)
{
	if (LevelInfos.Num() < LevelIndex)
		return LevelInfos[LevelIndex];
	return FName("");
}
