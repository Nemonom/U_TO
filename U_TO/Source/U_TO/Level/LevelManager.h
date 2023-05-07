// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

class U_TO_API LevelManager
{
public:
	LevelManager();
	~LevelManager();

	static LevelManager* GetInstance();
	FName GetLevelInfo(int LevelIndex);

private:
	TArray<FName> LevelInfos;
	static LevelManager* Instance;
};