
#include "ItemObject.h"
#include "../GameObject/Player/PlayerObject.h"
#include "../Weapon/WeaponObject.h"

AItemObject::AItemObject()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	Trigger->SetCollisionProfileName(TEXT("ItemBox"));

	RootComponent = Trigger;

	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	Box->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));
	if (SM_BOX.Succeeded())
		Box->SetStaticMesh(SM_BOX.Object);

	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	Box->SetCollisionProfileName(TEXT("NoCollision"));

	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	Effect->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_OPEN(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));

	if (P_OPEN.Succeeded())
	{
		Effect->SetTemplate(P_OPEN.Object);
		Effect->bAutoActivate = false;
	}


	WeaponItemClass = AWeaponObject::StaticClass();
}

void AItemObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AItemObject::OnCharacterOverlap);
}

void AItemObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemObject::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto MyCharacter = Cast<APlayerObject>(OtherActor);

	if (nullptr != MyCharacter && nullptr != WeaponItemClass)
	{
		auto NewWeapon = GetWorld()->SpawnActor<AWeaponObject>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
		NewWeapon->Init(EWeaponType::TEST2);
		MyCharacter->SetWeapon(NewWeapon);
		Box->SetHiddenInGame(true, true);
		SetActorEnableCollision(false);
		Effect->Activate(true);
		Effect->OnSystemFinished.AddDynamic(this, &AItemObject::OnEffectFinished);
	}
}

void AItemObject::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}
