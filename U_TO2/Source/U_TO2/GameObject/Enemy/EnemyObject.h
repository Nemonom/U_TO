// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Common/U_TOCommon.h"
#include "../BaseGameObject.h"
#include "EnemyObject.generated.h"

UCLASS()
class U_TO2_API AEnemyObject : public AActiveGameObject
{
	GENERATED_BODY()

public:
	AEnemyObject();
	virtual ~AEnemyObject();

	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	virtual void Init(EObjType Type) override;
	void SetPos(FVector ActorLocation);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;
	virtual void Die() override;

public:
	UPROPERTY(VisibleAnywhere, Category = Effect)
		UParticleSystemComponent* Effect;

private:
	UPROPERTY()
		class UPlayerAnimInstance* Anim{ nullptr };

	class Machine* AttackMachine{ nullptr };
};
