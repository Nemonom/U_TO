// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"
#include "Delegates/Delegate.h"

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

enum class ELevelType
{
	GAME,
	HELP,
	EXIT,
	MAX
};

enum class EViewMode
{
	FIRST,
	THIRD
};

enum class EObjType
{
	PLAYER,
	BOSS,
	ENEMY
};

enum class EAttackType
{
	PLAYER,
	ENEMY
};

enum class EWeaponType
{
	TEST1,
	TEST2
};

enum class EPassiveObjType
{
	TEST,
	ITEM
};

enum class ESpringArmLength
{
	THIRD_PERSON = 600,
};

enum class ESectionState : uint8
{
	READY = 0,
	BATTLE,
	COMPLETE
};