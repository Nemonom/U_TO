// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameInputMode;
	SetInputMode(GameInputMode);
	bShowMouseCursor = true;
}

void AMyPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}