// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerObject.h"
#include "../../Common/U_TOCommon.h"

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
}

void APlayerObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerObject::GoBack);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerObject::LeftRight);
}

void APlayerObject::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void APlayerObject::BeginPlay()
{
	Super::BeginPlay();

	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	//UAnimationAsset* AniAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Book/Animations/WarriorRun.WarriorRun"));
	//if (AniAsset)
	//	GetMesh()->PlayAnimation(AniAsset, true);
}

void APlayerObject::GoBack(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue * 200);
}

void APlayerObject::LeftRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue * 200);
}
