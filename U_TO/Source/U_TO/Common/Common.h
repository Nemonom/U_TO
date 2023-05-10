// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../U_TOGameModeBase.h"
#include "Common.generated.h"

UENUM()
enum class EScene
{
	LOGO,
	MENU,
	GAME,
	HELP,
	PAUSE,
	CLEAR,
	END
};

enum class EObjState
{
	NORMAL,
	DIE,
	END
};

enum class EGameState
{
	PLAY,
	OVER,
	CLEAR,
	END
};