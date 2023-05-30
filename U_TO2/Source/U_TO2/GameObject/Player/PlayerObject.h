// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseGameObject.h"
#include "../../Common/U_TOCommon.h"
#include "PlayerObject.generated.h"

/**
 * 
 */
UCLASS()
class U_TO2_API APlayerObject : public AActiveGameObject
{
	GENERATED_BODY()

public:
	APlayerObject();

	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	bool GetIsUsingDash();
	void SetWeapon(class AWeaponObject* NewWeapon);

protected:
	virtual void BeginPlay() override;
	virtual void Die() override;

	void SetControlMode(int32 ControlMode);

	UFUNCTION()
		virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp
			, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:
	void GoForward(float AxisValue);
	void LeftRight(float AxisValue);
	void LookUp(float AxisValue);
	void Rotate(float AxisValue);

	void ChangeView();
	void Attack();

	void SetDash(bool Enable);

	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
		class AWeaponObject* Weapon;

private:
	UPROPERTY()
		class UPlayerAnimInstance* Anim{ nullptr };

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking{ false };

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool CanNextCombo{ false };

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsComboInputOn{ false };

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		int32 CurrentCombo{ 0 };

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		int32 MaxCombo { 4 };

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange{ 0 };

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius{ 0 };

	EViewMode CurrentControlMode{ EViewMode::THIRD };

	bool IsUsingDash{ false };
};
