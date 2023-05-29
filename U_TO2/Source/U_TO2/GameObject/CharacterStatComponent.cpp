#include "CharacterStatComponent.h"
#include "../Script/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

UCharacterStatComponent::UCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetLevel(Level);
}

void UCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCharacterStatComponent::SetLevel(int32 InputLevel)
{
	auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr == GameInstance)
		return;

	CurrentStatData = GameInstance->GetCharacterData(InputLevel);
	if (CurrentStatData)
	{
		Level = InputLevel;
		SetHP(CurrentStatData->MaxHP);
	}
}

void UCharacterStatComponent::SetHP(int32 Hp)
{
	CurrentHP = Hp;
}

void UCharacterStatComponent::SetDamage(float NewDamage)
{
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
	if (CurrentHP <= 0.f)
		OnHPIsZero.Broadcast();
}

float UCharacterStatComponent::GetAttack()
{
	return CurrentStatData->Attack;
}

float UCharacterStatComponent::GetHPRatio()
{

	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}
