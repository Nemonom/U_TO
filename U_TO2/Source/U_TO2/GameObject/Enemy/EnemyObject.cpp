#include "EnemyObject.h"
#include "../CharacterStatComponent.h"
#include "../../Ani/PlayerAnimInstance.h"

AEnemyObject::AEnemyObject()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Warrior.SK_CharM_Warrior"));
	if (SK_CARDBOARD.Succeeded())
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANI(TEXT("/Game/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (WARRIOR_ANI.Succeeded())
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANI.Class);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerObject"));
}


void AEnemyObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Anim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == Anim)
		return;

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

	//FString MeshPath;

	//if (ObjType == EObjType::BOSS)
	//	MeshPath = TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Warrior.SK_CharM_Warrior");
	//else if (ObjType == EObjType::ENEMY)
	//	MeshPath = TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Golden.SK_CharM_Golden");

	//USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, *MeshPath);
	//if (SkeletalMesh)
	//	GetMesh()->SetSkeletalMesh(SkeletalMesh);

	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);

	//MeshPath = TEXT("/Game/WarriorAnimBlueprint.WarriorAnimBlueprint");

	//auto test = Cast<UAnimInstance>(LoadObject<UObject>(NULL, *MeshPath));
	//UAnimInstance* AniInstance = test;
	//if (AniInstance)
	//	GetMesh()->SetAnimInstanceClass(AniInstance->GetClass());

	RootComponent->SetRelativeLocationAndRotation(FVector(rand() % PosRange, rand() % PosRange, rand() % PosRange), FRotator(0, 0, 0));
	
	Super::Init(Type);
}

float AEnemyObject::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CharacterStat->SetDamage(ActualDamage);

	return ActualDamage;
}

void AEnemyObject::Die()
{
	Anim->SetDeadAnim(true);
	Super::Die();
}
