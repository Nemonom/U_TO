// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Common/Common.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/Classes/Particles/ParticleSystemComponent.h"
#include "BaseGameObject.generated.h"

UCLASS()
class U_TO_API ABaseGameObject : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseGameObject();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

protected:
	EObjState				ObjState_{ EObjState::NORMAL };
	UPrimitiveComponent*	CollisionComponent_{ nullptr };
};

UCLASS()
class U_TO_API APassiveGameObject : public ABaseGameObject
{
	GENERATED_BODY()

public:
	APassiveGameObject();

public:
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

UCLASS()
class U_TO_API AActiveGameObject : public ABaseGameObject
{
	GENERATED_BODY()

public:
	AActiveGameObject();

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

private:
	bool CheckDie();

protected:
	UParticleSystem*		DestroyEffect_{ nullptr };

private:
	float 					Hp_{ 0.f };
};
