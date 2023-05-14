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
class U_TO2_API APlayerObject : public ABaseGameObject
{
	GENERATED_BODY()

public:
	APlayerObject();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

protected:
	virtual void BeginPlay() override;

	void SetControlMode(int32 ControlMode);

private:
	void GoForward(float AxisValue);
	void LeftRight(float AxisValue);
	void LookUp(float AxisValue);
	void Rotate(float AxisValue);

	void ChangeView();

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;

private:
	EViewMode CurrentControlMode{ EViewMode::THIRD };
};
