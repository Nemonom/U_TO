// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameInputMode;
	SetInputMode(GameInputMode);
	bShowMouseCursor = true;
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);
	InputComponent->BindAxis("LookUp", this, &AMyPlayerController::LookUp);
	InputComponent->BindAxis("Rotate", this, &AMyPlayerController::Rotate);
}

void AMyPlayerController::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		FVector Direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X);
		GetPawn()->AddMovementInput(Direction, Value * MovementSpeed * GetWorld()->GetDeltaSeconds());
	}
}

void AMyPlayerController::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		FVector Direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y);
		GetPawn()->AddMovementInput(Direction, Value * MovementSpeed * GetWorld()->GetDeltaSeconds());
	}
}

void AMyPlayerController::LookUp(float Value)
{
	if (Value != 0.0f)
	{
		//float MouseDelta = Value * CameraSensitivity * GetWorld()->GetDeltaSeconds();
		AddPitchInput(Value);
	}
}

void AMyPlayerController::Rotate(float Value)
{
	if (Value != 0.0f)
	{
		//float MouseDelta = Value * CameraSensitivity * GetWorld()->GetDeltaSeconds();
		AddYawInput(Value);
	}
}