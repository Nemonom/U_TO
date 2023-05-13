// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameObject/MyPlayerController.h"
#include "GameObject/BaseGameObject.h"
#include "U_TOGameModeBase.generated.h"

UCLASS()
class U_TO_API AU_TOGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AU_TOGameModeBase();

	virtual void PostLogin(APlayerController* NewPlayer) override;
};
