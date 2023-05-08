// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuUI.h"
#include "Kismet/GameplayStatics.h"
#include "../Level/LevelManager.h"
#include "UMG.h"

void UMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < (int)EButtonType::Max; ++i)
	{
		FString ButtonName = FString::Printf(TEXT("btn_%d"), i);
		UButton* tempButton = Cast<UButton>(GetWidgetFromName(*ButtonName));
		MenuButton_.Add(tempButton);
	}
}

void UMenuUI::ChangeLevel(int LevelIndex)
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelManager::GetInstance()->GetLevelInfo(LevelIndex));
}

