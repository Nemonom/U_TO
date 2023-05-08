// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuLevel.h"
#include "../UI/MenuUI.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"


void AMenuLevel::BeginPlay()
{
	Super::BeginPlay();

	//APlayerController* PlayerController = nullptr;
	//for (TActorIterator<APlayerController> iter(GetWorld()); iter; ++iter)
	//{
	//	PlayerController = *iter;
	//	break;
	//}
	//UMenuUI* YourWidget = CreateWidget<UMenuUI>(PlayerController, UMenuUI::StaticClass());
	//if (YourWidget)
	//	YourWidget->AddToViewport();

	FStringClassReference MyWidgetClassRef(TEXT("/Game/menu_BP.menu_BP_C"));
	UClass* WidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>();
	if (WidgetClass)
	{
		UMenuUI* menuWidget = Cast<UMenuUI>(CreateWidget<UUserWidget>(this->GetGameInstance(), WidgetClass));
		if (menuWidget)
			menuWidget->AddToViewport();
	}
}

void AMenuLevel::Test()
{
}
