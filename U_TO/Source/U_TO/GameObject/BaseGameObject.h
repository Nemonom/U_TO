// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Common/Common.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseGameObject.generated.h"

UCLASS()
class U_TO_API ABaseGameObject : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseGameObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	EObjState ObjState_{ EObjState::NORMAL };
	UPrimitiveComponent* MyCollisionComponent_;
};
