// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGameObject.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base
ABaseGameObject::ABaseGameObject()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent_ = CreateDefaultSubobject<UPrimitiveComponent>(TEXT("CollisionComponent"));
}

void ABaseGameObject::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseGameObject::Destroyed()
{
	Super::Destroyed();
}

void ABaseGameObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGameObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseGameObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
#pragma endregion


#pragma region Passive
APassiveGameObject::APassiveGameObject()
{
}

void APassiveGameObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
#pragma endregion

#pragma region Active
AActiveGameObject::AActiveGameObject()
{
	//// 활성화 또는 비활성화시킬 수 있는 파티클 시스템 생성
	//OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	//OurParticleSystem->SetupAttachment(SphereVisual);
	//OurParticleSystem->bAutoActivate = false;
	//OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	//if (ParticleAsset.Succeeded())
	//{
	//	OurParticleSystem->SetTemplate(ParticleAsset.Object);
	//}
}

void AActiveGameObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Hp_ -= data;
	
	if (CheckDie())
	{
		Destroyed();
	}
}

void AActiveGameObject::BeginPlay()
{
	CollisionComponent_->OnComponentBeginOverlap.AddDynamic(this, &AActiveGameObject::OnOverlapBegin);
}

void AActiveGameObject::Destroyed()
{
	if (DestroyEffect_)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyEffect_, GetActorLocation());

	Super::Destroyed();
}

bool AActiveGameObject::CheckDie()
{
	if (Hp_ <= 0)
		return true;
	return false;
}
#pragma endregion
