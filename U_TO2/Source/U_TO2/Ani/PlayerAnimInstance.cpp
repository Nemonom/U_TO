// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "../GameObject/Player/PlayerObject.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Book/Animations/SK_Mannequin_Skeleton_Montage.SK_Mannequin_Skeleton_Montage"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (false == ::IsValid(Pawn))
		return;

	if (false == IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();

		if (auto Character = Cast<APlayerObject>(Pawn))
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
			IsUsingDash = Character->GetIsUsingDash();
		}
	
	}
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.f);
}

void UPlayerAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

void UPlayerAnimInstance::SetDeadAnim(bool input)
{
	IsDead = input;
}

void UPlayerAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void UPlayerAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

FName UPlayerAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	UE_LOG(LogTemp, Warning, TEXT("Attack %d"), Section);
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}

