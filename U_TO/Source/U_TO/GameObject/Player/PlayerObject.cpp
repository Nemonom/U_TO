// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerObject.h"

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
	UAnimationAsset* AniAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Book/Animations/WarriorRun.WarriorRun"));
	if (AniAsset)
		GetMesh()->PlayAnimation(AniAsset, true);
	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	//static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/Book/Animations/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	//if (WARRIOR_ANIM.Succeeded())
	//{
	//	GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	//}
}

void APlayerObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("GB"), this, &APlayerObject::GoBack);
	PlayerInputComponent->BindAxis(TEXT("LR"), this, &APlayerObject::LeftRight);
//	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerObject::LookUp);
//	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerObject::Rotate);
}

void APlayerObject::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void APlayerObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APlayerObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void APlayerObject::Tick(float DeltaSeconds)
{
}

void APlayerObject::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerObject::GoBack(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue * 200);
}

void APlayerObject::LeftRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue * 200);
}
