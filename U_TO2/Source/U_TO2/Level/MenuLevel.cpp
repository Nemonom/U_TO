#include "MenuLevel.h"
#include "../UI/MenuUI.h"
#include "GameFramework/PlayerController.h"


void AMenuLevel::BeginPlay()
{
	Super::BeginPlay();

	FStringClassReference MyWidgetClassRef(TEXT("/Game/menu_BP.menu_BP_C"));
	WidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>();
	if (WidgetClass)
	{
		menuWidget = (CreateWidget<UMenuUI>(this->GetGameInstance(), WidgetClass));
		if (menuWidget)
			menuWidget->AddToViewport();
	}
}

void AMenuLevel::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (WidgetClass)
	{
		if (menuWidget)
		{
			menuWidget->RemoveFromViewport();
			menuWidget = nullptr;
		}
	}

	Super::EndPlay(EndPlayReason);
}