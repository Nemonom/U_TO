#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Common/U_TOCommon.h"
#include "BaseGameObject.generated.h"

UCLASS()
class U_TO2_API ABaseGameObject : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseGameObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Init();
};

UCLASS()
class U_TO2_API APassiveGameObject : public ABaseGameObject
{
	GENERATED_BODY()

public:
	APassiveGameObject();

	virtual void Init(EPassiveObjType Type);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp
			, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	EPassiveObjType ObjType{ EPassiveObjType::TEST };
};


UCLASS()
class U_TO2_API AActiveGameObject : public ABaseGameObject
{
	GENERATED_BODY()

public:
	AActiveGameObject();

	virtual void Init(EObjType Type);
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	void SetIsDead(bool input);
	bool GetIsDead();

protected:
	// notify
	void AttackCheck();

	virtual void Die();

protected:
	EObjType ObjType{ EObjType::PLAYER };
	bool IsDead{ false };
};