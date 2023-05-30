#include "EnemyObject.h"
#include "../CharacterStatComponent.h"

AEnemyObject::AEnemyObject()
{
}


void AEnemyObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		Die();
		});
}

void AEnemyObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyObject::Init(EObjType Type)
{
	ObjType = Type;

	int PosRange = ObjType == EObjType::BOSS ? 10 : 300;

	USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Golden.SK_CharM_Golden"));
	if (SkeletalMesh)
		GetMesh()->SetSkeletalMesh(SkeletalMesh);
	
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	RootComponent->SetRelativeLocationAndRotation(FVector(rand() % PosRange, rand() % PosRange, rand() % PosRange), FRotator(0, 0, 0));
	
	UAnimInstance* Anim = LoadObject<UAnimInstance>(nullptr, TEXT("/Game/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (Anim)
		GetMesh()->SetAnimInstanceClass(Anim->GetClass());

	Super::Init(Type);
}

float AEnemyObject::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CharacterStat->SetDamage(ActualDamage);

	return ActualDamage;
}
