// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGameObject.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base
ABaseGameObject::ABaseGameObject()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	CollisionComponent->SetCapsuleHalfHeight(88.f);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));

	CollisionComponent->SetupAttachment(RootComponent);
	MeshComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> 
		SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())
		MeshComponent->SetSkeletalMesh(SK_CARDBOARD.Object);
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
}

float AActiveGameObject::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Hp <= 0.f)
	{
		return 0.f;
	}

	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.f)
	{
		Hp -= ActualDamage;
		if (Hp <= 0)
		{
			Die(ActualDamage, DamageEvent, EventInstigator, DamageCauser);
		}

		MakeNoise(1.0f, EventInstigator ? EventInstigator->GetPawn() : this);
	}

	return ActualDamage;
}

bool AActiveGameObject::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	// GetWorld()->GetAuthGameMode<AShooterGameMode>()->Killed(Killer, KilledPlayer, this, DamageType);
	// Destroy();

	if (DestroyEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyEffect, GetActorLocation());

	return true;
}

void AActiveGameObject::BeginPlay()
{
	// CollisionComponent_->OnComponentBeginOverlap.AddDynamic(this, &AActiveGameObject::OnOverlapBegin);
}
#pragma endregion
