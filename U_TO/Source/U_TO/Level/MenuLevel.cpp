#include "MenuLevel.h"
#include "../UI/MenuUI.h"
#include "GameFramework/PlayerController.h"


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
		//UMenuUI* menuWidget = Cast<UMenuUI>(CreateWidget<UUserWidget>(this->GetGameInstance(), WidgetClass));
		UUserWidget* menuWidget = (CreateWidget<UUserWidget>(this->GetGameInstance(), WidgetClass));
		if (menuWidget)
			menuWidget->AddToViewport();
	}
}

void AMenuLevel::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//FStringClassReference MyWidgetClassRef(TEXT("/Game/menu_BP.menu_BP_C"));
	//UClass* WidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>();
	//if (WidgetClass)
	//{
	//	UMenuUI* MenuWidget = Cast<UMenuUI>(CreateWidget<UUserWidget>(this->GetGameInstance(), WidgetClass));
	//	if (MenuWidget)
	//	{
	//		MenuWidget->RemoveFromViewport();
	//		MenuWidget = nullptr;
	//	}
	//}

	Super::EndPlay(EndPlayReason);
}

void AMenuLevel::Test()
{
}
