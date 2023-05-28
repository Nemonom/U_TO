// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponObject.h"

// Sets default values
AWeaponObject::AWeaponObject()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight"));

	if (SK_WEAPON.Succeeded())
	{
		Weapon->SetSkeletalMesh(SK_WEAPON.Object);
	}

	Weapon->SetCollisionProfileName(TEXT("NoCollision"));
}

void AWeaponObject::Init(EWeaponType Type)
{
	WeaponType = Type;

	FString MeshPath;

	if (WeaponType == EWeaponType::TEST1)
		MeshPath = TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight");
	else if (WeaponType == EWeaponType::TEST2)
		MeshPath = TEXT("/Game/InfinityBladeWeapons/Weapons/Weapon_ForgingHammers/SK_Forging_ForgeHammer01.SK_Forging_ForgeHammer01");

	USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, *MeshPath);

	if (SkeletalMesh)
		Weapon->SetSkeletalMesh(SkeletalMesh);
}

// Called when the game starts or when spawned
void AWeaponObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

