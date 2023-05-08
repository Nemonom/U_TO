// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuUI.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class U_TO_API UMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	enum class EButtonType : int8
	{
		StartGame,
		Help,
		Exit,
		Max
	};

protected:
	virtual void NativeConstruct() override;
	void ChangeLevel(int LevelIndex);

protected:
	UPROPERTY()
		TArray<class UButton*> MenuButton_;
		//class UButton* MenuButton_[3];
};
