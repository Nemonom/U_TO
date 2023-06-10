#include "CharacterWidget.h"
#include "../GameObject/CharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UCharacterWidget::BindCharacterStat(UCharacterStatComponent* NewCharacterStat)
{
	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UCharacterWidget::UpdateHPWidget);
	NewCharacterStat->OnDestroy.BindLambda([&]()
		{
			CurrentCharacterStat = nullptr;
		});
}

void UCharacterWidget::SetCurrentEnemyStat(UCharacterStatComponent* NewEnemyStat)
{
	CurrentEnemyStat = NewEnemyStat;
	NewEnemyStat->OnHPChanged.AddUObject(this, &UCharacterWidget::UpdateHPWidget);
	NewEnemyStat->OnDestroy.BindLambda([&]()
		{
			CurrentEnemyStat = nullptr;
		});

}

void UCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	EnemyHPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("EnemyHPBar")));
	UpdateHPWidget();
}

void UCharacterWidget::UpdateHPWidget()
{
	//auto SetPercent = [](auto& Component) -> void
	//{
	//	Component->SetPercent(CurrentCharacterStat->GetHPRatio());
	//};

	if (CurrentCharacterStat.IsValid())
	{
		if (HPProgressBar)
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());

		if (EnemyHPProgressBar)
			EnemyHPProgressBar->SetPercent(CurrentEnemyStat->GetHPRatio());
	}
}
