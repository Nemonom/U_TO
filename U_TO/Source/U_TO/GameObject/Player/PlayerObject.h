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

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;

protected:
	virtual void BeginPlay() override;

private:
	void GoBack(float AxisValue);
	void LeftRight(float AxisValue);
};
