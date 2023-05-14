// Copyright Epic Games, Inc. All Rights Reserved.


#include "U_TOGameModeBase.h"

AU_TOGameModeBase::AU_TOGameModeBase()
{
	//DefaultPawnClass = APlayerObject::StaticClass();
	DefaultPawnClass = AABCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}

void AU_TOGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}