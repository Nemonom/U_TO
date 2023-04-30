// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
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

UENUM()
enum class EObjState
{
	NORMAL,
	DIE,
	END
};

UENUM()
enum class EGameState
{
	PLAY,
	OVER,
	CLEAR,
	END
};