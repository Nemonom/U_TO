// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameLevel.generated.h"

UCLASS()
class U_TO2_API AGameLevel : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

private:
	class EnemyManager* EnemyManager_;
	TArray<TSharedPtr<class APassiveGameObject>> PassiveObject;
};
