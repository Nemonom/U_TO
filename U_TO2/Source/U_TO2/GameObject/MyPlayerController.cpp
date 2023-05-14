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
