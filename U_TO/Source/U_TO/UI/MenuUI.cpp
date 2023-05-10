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

		if (i == (int)LevelManager::ELevelType::Game)
			tempButton->OnClicked.AddDynamic(this, &UMenuUI::OnClickGameButton);
		else if (i == (int)LevelManager::ELevelType::Exit)
			tempButton->OnClicked.AddDynamic(this, &UMenuUI::OnClickExitButton);

		MenuButton_.Add(tempButton);
	}
}

void UMenuUI::OnClickGameButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("GAME"));
}

void UMenuUI::OnClickExitButton()
{
	exit(0);
}
