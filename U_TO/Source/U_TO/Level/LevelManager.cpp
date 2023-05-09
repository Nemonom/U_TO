#include "LevelManager.h"
#include "../Common/Common.h"

LevelManager* LevelManager::Instance = nullptr;

LevelManager::LevelManager()
{
	//LevelInfos.Add(FName("Game"));
	//LevelInfos.Add(FName("Help"));
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

//FName LevelManager::GetLevelInfo(int LevelIndex)
//{
//	if (LevelInfos.Num() < LevelIndex)
//		return LevelInfos[LevelIndex];
//	return FName("");
//}

FName LevelManager::GetLevelName(ELevelType type)
{
	switch (type)
	{
		case ELevelType::Game:
		{
			return FName("Game");
		}
		break;
		case ELevelType::Help:
		{
			return FName("Help");
		}
		break;
		case ELevelType::Exit:
		{
			return FName("Exit");
		}
		break;
	}

	return FName("");
}

void LevelManager::ChangeLevel(const UObject* WorldContextObject, ELevelType type)
{
	UGameplayStatics::OpenLevel(WorldContextObject, GetLevelName(type));
}
