// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Common/Common.h"
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
	APlayerObject();

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;

protected:
	virtual void BeginPlay() override;
};
