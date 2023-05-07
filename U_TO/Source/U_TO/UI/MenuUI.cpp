// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuUI.h"
#include "Kismet/GameplayStatics.h"
#include "../Level/LevelManager.h"

void UMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	// test
	//for (int i = 0; i < (int)EButtonType::Max; ++i)
	//	MenuButton_[i] = Cast<UButton>(GetWidgetFromName(TEXT("pBar_Stamina")));
}

void UMenuUI::ChangeLevel(int LevelIndex)
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelManager::GetInstance()->GetLevelInfo(LevelIndex));
}

