#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Common/U_TOCommon.h"
#include "ProjectileObject.generated.h"

UCLASS()
class U_TO2_API AProjectileObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileObject();

	void FireInDirection(const FVector& ShootDirection);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;
};
