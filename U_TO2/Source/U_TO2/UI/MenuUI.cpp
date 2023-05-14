// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuUI.h"
#include "UMG.h"
#include "../Common/U_TOCommon.h"

void UMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < (int)ELevelType::MAX; ++i)
	{
		FString ButtonName = FString::Printf(TEXT("Button_%d"), i);
		UButton* tempButton = Cast<UButton>(GetWidgetFromName(*ButtonName));

		if (i == (int)ELevelType::GAME)
			tempButton->OnClicked.AddDynamic(this, &UMenuUI::OnClickGameButton);
		else if (i == (int)ELevelType::EXIT)
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
