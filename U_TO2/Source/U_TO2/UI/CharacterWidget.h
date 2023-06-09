#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class U_TO2_API UCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UCharacterStatComponent* NewCharacterStat);

	void SetCurrentEnemyStat(UCharacterStatComponent* NewEnemyStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
		class UProgressBar* HPProgressBar;

	UPROPERTY()
		class UProgressBar* EnemyHPProgressBar;

	TWeakObjectPtr<class UCharacterStatComponent> CurrentEnemyStat{ nullptr };
};
