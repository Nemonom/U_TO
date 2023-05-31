// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 *
 */
UCLASS()
class U_TO2_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* aPawn) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Rotate(float Value);

private:
	UPROPERTY(EditDefaultsOnly)
		float MovementSpeed{ 500.0f };

	UPROPERTY(EditDefaultsOnly)
		float CameraSensitivity{ 1.0f };
};
