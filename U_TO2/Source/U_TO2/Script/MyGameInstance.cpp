// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"


UMyGameInstance::UMyGameInstance()
{
	FString CharacterDataPath = TEXT("/Game/Book/GameData/CharacterData.CharacterData");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABCHARACTER(*CharacterDataPath);
	CharacterTable = DT_ABCHARACTER.Object;
}

void UMyGameInstance::Init()
{
	Super::Init();
}

FCharacterData* UMyGameInstance::GetCharacterData(int32 Level)
{
	return CharacterTable->FindRow<FCharacterData>(*FString::FromInt(Level), TEXT(""));
}
