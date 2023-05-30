#include "CharacterWidget.h"
#include "../GameObject/CharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UCharacterWidget::BindCharacterStat(UCharacterStatComponent* NewCharacterStat)
{
	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UCharacterWidget::UpdateHPWidget);
}

void UCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	UpdateHPWidget();
}

void UCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (HPProgressBar)
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
	}
}
