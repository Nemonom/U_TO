// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerObject.h"
#include "../../Ani/PlayerAnimInstance.h"
#include "../../Weapon/WeaponObject.h"
#include "DrawDebugHelpers.h"

APlayerObject::APlayerObject()
{
	ObjType = EObjType::PLAYER;

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

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerObject"));


	SetControlMode(0);

	GetCharacterMovement()->JumpZVelocity = 800.f;

	AttackEndComboState();


	AttackRange = 200.0f;
	AttackRadius = 50.0f;

	Hp = 5;
	Power = 2;
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
		//if (IsComboInputOn)
		{
			AttackStartComboState();
			Anim->JumpToAttackMontageSection(CurrentCombo);
		}
		});

	Anim->OnAttackHitCheck.AddUObject(this, &APlayerObject::AttackCheck);
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

float APlayerObject::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (Hp <= 0.f)
		Die();

	return ActualDamage;
}

bool APlayerObject::GetIsUsingDash()
{
	return IsUsingDash;
}

void APlayerObject::BeginPlay()
{
	Super::BeginPlay();

	//FName WeaponSocket(TEXT("hand_rSocket"));
	//if (auto CurWeapon = GetWorld()->SpawnActor<AWeaponObject>(FVector::ZeroVector, FRotator::ZeroRotator))
	//	CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerObject::OnBeginOverlap);
}

void APlayerObject::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("coll"));
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
		CurrentCombo %= 4;
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
			HitResult.Actor->TakeDamage(Power, DamageEvent, GetController(), this);
		}
	}
}