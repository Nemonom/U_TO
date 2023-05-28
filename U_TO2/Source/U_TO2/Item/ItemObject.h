#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Common/U_TOCommon.h"
#include "ItemObject.generated.h"

UCLASS()
class U_TO2_API AItemObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemObject();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Box)
		UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
		UStaticMeshComponent* Box;

	UPROPERTY(EditInstanceOnly, Category = Box)
		TSubclassOf<class AWeaponObject> WeaponItemClass;

	UPROPERTY(VisibleAnywhere, Category = Effect)
		UParticleSystemComponent* Effect;

private:
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEffectFinished(class UParticleSystemComponent* PSystem);
};
