// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyObject.h"

#define ENEMY_MESH_PATH "/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"
#define BOSS_MESH_PATH "/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"

#define ENEMY_ANI_PATH "/Game/WarriorAnimBlueprint.WarriorAnimBlueprint_C"
#define BOSS_ANI_PATH "/Game/WarriorAnimBlueprint.WarriorAnimBlueprint_C"

AEnemyObject::AEnemyObject()
{
}


void AEnemyObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEnemyObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyObject::Init(EObjType Type)
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT(ENEMY_MESH_PATH));
	if (SK_CARDBOARD.Succeeded())
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);


	GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANI(TEXT(ENEMY_ANI_PATH));
	if (WARRIOR_ANI.Succeeded())
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANI.Class);
	
	int PosRange = ObjType == EObjType::BOSS ? 10 : 300;
	GetMesh()->SetRelativeLocationAndRotation(FVector(rand() % PosRange, rand() % PosRange, rand() % PosRange), FRotator(0, 0, 0));

	Super::Init(Type);
}
