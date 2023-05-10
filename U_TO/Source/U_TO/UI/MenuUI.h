#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuUI.generated.h"

/**
 * 
 */
UCLASS()
class U_TO_API UMenuUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
		void OnClickGameButton();
	UFUNCTION(BlueprintCallable)
		void OnClickExitButton();

protected:
	UPROPERTY()
		TArray<class UButton*> MenuButton_;
};
