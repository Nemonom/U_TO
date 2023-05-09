#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

class U_TO_API LevelManager
{
public:
	enum class ELevelType
	{
		Game,
		Help,
		Exit,
		Max
	};

public:
	LevelManager();
	~LevelManager();

	static LevelManager* GetInstance();
	//FName GetLevelInfo(int LevelIndex);
	FName GetLevelName(ELevelType type);
	void ChangeLevel(const UObject* WorldContextObject, ELevelType type);

private:
	//TArray<FName> LevelInfos;
	static LevelManager* Instance;
};