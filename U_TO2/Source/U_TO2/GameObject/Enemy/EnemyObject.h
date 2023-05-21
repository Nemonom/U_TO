// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Common/U_TOCommon.h"
#include "../BaseGameObject.h"
#include "EnemyObject.generated.h"

UCLASS()
class U_TO2_API AEnemyObject : public ABaseGameObject
{
	GENERATED_BODY()
	
public:
	AEnemyObject();
	AEnemyObject(EObjType Type);

	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

};
