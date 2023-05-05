// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameLevel.generated.h"

class EnemyManager;

UCLASS()
class U_TO_API AGameLevel : public ALevelScriptActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	EnemyManager* EnemyManager_;
};
