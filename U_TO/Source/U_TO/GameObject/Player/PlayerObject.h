// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseGameObject.h"
#include "PlayerObject.generated.h"

/**
 * 
 */
UCLASS()
class U_TO_API APlayerObject : public AActiveGameObject
{
	GENERATED_BODY()

public:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;
};
