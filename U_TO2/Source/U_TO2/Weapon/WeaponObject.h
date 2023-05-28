// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common/U_TOCommon.h"
#include "GameFramework/Actor.h"
#include "WeaponObject.generated.h"

UCLASS()
class U_TO2_API AWeaponObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponObject();

	void Init(EWeaponType Type);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
		class USkeletalMeshComponent* Weapon;

	EWeaponType WeaponType;
};
