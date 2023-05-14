// Copyright Epic Games, Inc. All Rights Reserved.

#include "U_TO2GameMode.h"
#include "U_TO2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "GameObject/Player/PlayerObject.h"
#include "GameObject/MyPlayerController.h"

AU_TO2GameMode::AU_TO2GameMode()
{
	DefaultPawnClass = APlayerObject::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
