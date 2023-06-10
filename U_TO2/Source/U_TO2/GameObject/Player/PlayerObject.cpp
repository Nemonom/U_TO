// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerObject.h"
#include "../../Ani/PlayerAnimInstance.h"
#include "../../Weapon/WeaponObject.h"
#include "../CharacterStatComponent.h"
#include "../Projectile/Machine/LookShotMachine.h"

APlayerObject::APlayerObject()
{
	ObjType = EObjType::PLAYER;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->TargetArmLength = 400.f; 
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	ThirdPersonCamera->SetupAttachment(SpringArm);

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight));
	FirstPersonCamera->bUsePawnControlRotation = true;
	FirstPersonCamera->SetActive(false);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);


	GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANI(TEXT("/Game/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (WARRIOR_ANI.Succeeded())
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANI.Class);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerObject"));


	SetControlMode(EViewMode::THIRD);

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;

	AttackEndComboState();

	AttackRange = 200.0f;
	AttackRadius = 50.0f;
}

void APlayerObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AttackMachine)
	{
		AttackMachine->SetPos(GetActorLocation());
		AttackMachine->SetDir(GetActorRotation().Vector());
	}
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
			UE_LOG(LogTemp, Warning, TEXT("JumpToAttackMontageSection %d"), CurrentCombo);
			Anim->JumpToAttackMontageSection(CurrentCombo);
		}
		});


	Anim->OnAttackHitCheck.AddUObject(this, &APlayerObject::AttackCheck);


	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		Die();
		});
}

void APlayerObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("ChangeView"), EInputEvent::IE_Pressed, this, &APlayerObject::ChangeView);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayerObject::Attack);
}

void APlayerObject::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

float APlayerObject::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CharacterStat->SetDamage(ActualDamage);

	return ActualDamage;
}

bool APlayerObject::GetIsUsingDash()
{
	return IsUsingDash;
}

void APlayerObject::BeginPlay()
{
	Super::BeginPlay();

	AttackMachine = new LookShotMachine(GetWorld(), EAttackType::PLAYER);
	AttackMachine->SetPos(GetActorLocation());

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerObject::OnBeginOverlap);

	if (IsPlayerControlled())
	{
		EnableInput(Cast<APlayerController>(GetController()));
	}
}

void APlayerObject::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void APlayerObject::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("collision"));
}

void APlayerObject::SetWeapon(AWeaponObject* NewWeapon)
{
	FName WeaponSocket(TEXT("hand_rSocket"));
	if (nullptr != NewWeapon)
	{
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);
		Weapon = NewWeapon;
	}
}

void APlayerObject::Die()
{
	Anim->SetDeadAnim(true);

	Super::Die();
}

void APlayerObject::SetControlMode(EViewMode ControlMode)
{
	if (ControlMode == EViewMode::THIRD)
	{
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);

		FirstPersonCamera->SetActive(false);
		ThirdPersonCamera->SetActive(true);

		bUseControllerRotationYaw = false;

		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
	}
	else if (ControlMode == EViewMode::FIRST)
	{
		FirstPersonCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 150.0f));
		FirstPersonCamera->bUsePawnControlRotation = true;

		FirstPersonCamera->SetActive(true);
		ThirdPersonCamera->SetActive(false);

		bUseControllerRotationYaw = true;

		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
	}
	CurrentControlMode = ControlMode;
}

void APlayerObject::ChangeView()
{
	switch (CurrentControlMode)
	{
	case EViewMode::THIRD:
		SetControlMode(EViewMode::FIRST);
		break;
	case EViewMode::FIRST:
		SetControlMode(EViewMode::THIRD);
		break;
	}
}

void APlayerObject::Attack()
{
	if (IsAttacking)
	{
		if (CanNextCombo)
			IsComboInputOn = true;
	}
	else
	{
		AttackStartComboState();
		Anim->PlayAttackMontage();
		Anim->JumpToAttackMontageSection(CurrentCombo);
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


void APlayerObject::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);

#endif

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);
		}
	}
}