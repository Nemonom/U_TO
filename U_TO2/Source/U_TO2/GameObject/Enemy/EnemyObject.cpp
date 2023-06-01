#include "EnemyObject.h"
#include "../CharacterStatComponent.h"
#include "../../Ani/PlayerAnimInstance.h"
#include "../Projectile/Machine/WaveMachine.h"

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

	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	Effect->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_OPEN(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));

	if (P_OPEN.Succeeded())
	{
		Effect->SetTemplate(P_OPEN.Object);
		Effect->bAutoActivate = false;
	}

	AttackMachine = new WaveMachine();
	AttackMachine->SetWorld(GetWorld());
	AttackMachine->SetPos(GetActorLocation());
}


void AEnemyObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Anim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		Die();
		});
}

void AEnemyObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AttackMachine->Tick(DeltaTime);
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
	//UAnimationAsset* test = LoadObject<UAnimationAsset>(NULL, *MeshPath);
	//GetMesh()->PlayAnimation(test, true);

	RootComponent->SetRelativeLocationAndRotation(FVector(rand() % PosRange, rand() % PosRange, 0), FRotator(0, 0, 0));

	Super::Init(Type);
}

float AEnemyObject::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CharacterStat->SetDamage(ActualDamage);

	return ActualDamage;
}

void AEnemyObject::BeginPlay()
{
	Super::BeginPlay();

	Effect->Activate(true);
}

void AEnemyObject::Die()
{
	Anim->SetDeadAnim(true);
	Super::Die();
}
