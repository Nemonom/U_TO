// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerObject.h"
#include "../../Ani/PlayerAnimInstance.h"

APlayerObject::APlayerObject()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArm->SetupAttachment(GetCapsuleComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);


	GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANI(TEXT("/Game/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (WARRIOR_ANI.Succeeded())
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANI.Class);

	SetControlMode(0);

	GetCharacterMovement()->JumpZVelocity = 800.f;

	AttackEndComboState();
}

void APlayerObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Anim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == Anim)
		return;

	Anim->OnMontageEnded.AddDynamic(this, &APlayerObject::OnAttackMontageEnded);

	Anim->OnNextAttackCheck.AddLambda([this]() -> void {
		CanNextCombo = false;
		if (IsComboInputOn)
		{
			AttackStartComboState();
			Anim->JumpToAttackMontageSection(CurrentCombo);
		}
		});

}

void APlayerObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerObject::GoForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerObject::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerObject::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Rotate"), this, &APlayerObject::Rotate);

	PlayerInputComponent->BindAction(TEXT("ChangeView"), EInputEvent::IE_Pressed, this, &APlayerObject::ChangeView);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayerObject::Attack);

}

void APlayerObject::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

bool APlayerObject::GetIsUsingDash()
{
	return IsUsingDash;
}

void APlayerObject::BeginPlay()
{
	Super::BeginPlay();

	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	//UAnimationAsset* AniAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Book/Animations/WarriorRun.WarriorRun"));
	//if (AniAsset)
	//	GetMesh()->PlayAnimation(AniAsset, true);
}

void APlayerObject::SetControlMode(int32 ControlMode)
{
	if (ControlMode == 0)
	{
		SpringArm->TargetArmLength = 450.0f;
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	}
}

void APlayerObject::GoForward(float AxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), AxisValue);
}

void APlayerObject::LeftRight(float AxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), AxisValue);
}

void APlayerObject::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void APlayerObject::Rotate(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayerObject::ChangeView()
{
	//switch (CurrentControlMode)
	//{
	//case EViewMode::THIRD:
	//	GetController()->SetControlRotation(GetActorRotation());
	//	SetControlMode(EViewMode::FIRST);
	//	break;
	//}
}

void APlayerObject::Attack()
{
	if (IsAttacking)
	{
		if (CanNextCombo)
		{
			IsComboInputOn = true;
		}
		Anim->JumpToAttackMontageSection(CurrentCombo);
		CurrentCombo++;
		CurrentCombo %= 5;
		// 코드 수정
	}
	else
	{
		AttackStartComboState();
		Anim->PlayAttackMontage();
		//Anim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}
}

void APlayerObject::SetDash(bool Enable)
{
	IsUsingDash = Enable;
}

void APlayerObject::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	AttackEndComboState();
}

void APlayerObject::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void APlayerObject::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}
