// Copyright Epic Games, Inc. All Rights Reserved.


#include "U_TOGameModeBase.h"

AU_TOGameModeBase::AU_TOGameModeBase()
{
	DefaultPawnClass = ABaseGameObject::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
