// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerObject.h"

APlayerObject::APlayerObject()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArmComponent->SetupAttachment(CollisionComponent);
	Camera->SetupAttachment(SpringArmComponent);
}

void APlayerObject::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}