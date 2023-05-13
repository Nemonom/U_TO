// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerObject.h"

APlayerObject::APlayerObject()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArmComponent->TargetArmLength = 400.f;
	SpringArmComponent->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArmComponent->SetupAttachment(CollisionComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArmComponent);


}

void APlayerObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("GB"), this, &APlayerObject::GoBack);
	PlayerInputComponent->BindAxis(TEXT("LR"), this, &APlayerObject::LeftRight);
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

	if (MeshComponent)
	{
		MeshComponent->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		UAnimationAsset* AniAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Book/Animations/WarriorRun.WarriorRun"));
		if (AniAsset)
			MeshComponent->PlayAnimation(AniAsset, true);
	}
}

void APlayerObject::GoBack(float AxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), AxisValue * 200);
}

void APlayerObject::LeftRight(float AxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), AxisValue * 200);
}
