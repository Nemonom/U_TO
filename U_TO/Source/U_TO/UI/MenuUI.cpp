#include "MenuUI.h"
#include "../Level/LevelManager.h"
#include "UMG.h"

void UMenuUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	for (int i = 0; i < (int)LevelManager::ELevelType::Max; ++i)
	{
		FString ButtonName = FString::Printf(TEXT("btn_%d"), i);
		UButton* tempButton = Cast<UButton>(GetWidgetFromName(*ButtonName));
		tempButton->OnClicked.AddDynamic(this, &UMenuUI::ChangeLevel);
		MenuButton_.Add(tempButton);
	}
}

void UMenuUI::ChangeLevel()
{
	LevelManager::GetInstance()->ChangeLevel(GetWorld(), LevelManager::ELevelType::Game);
}
