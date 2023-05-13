// Copyright Epic Games, Inc. All Rights Reserved.


#include "U_TOGameModeBase.h"

AU_TOGameModeBase::AU_TOGameModeBase()
{
	DefaultPawnClass = ABaseGameObject::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}

void AU_TOGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	FString::Printf(TEXT("GameModePostLogin Start"));
	Super::PostLogin(NewPlayer);
	FString::Printf(TEXT("GameModePostLogin End"));
}