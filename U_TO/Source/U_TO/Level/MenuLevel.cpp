// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuLevel.h"
#include "../UI/MenuUI.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"

void AMenuLevel::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = nullptr;
	for (TActorIterator<APlayerController> iter(GetWorld()); iter; ++iter)
	{
		PlayerController = *iter;
		break;
	}
	UMenuUI* YourWidget = CreateWidget<UMenuUI>(PlayerController, UMenuUI::StaticClass());
	YourWidget->AddToViewport();
}

void AMenuLevel::Test()
{
}
