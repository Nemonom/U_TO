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

	UFUNCTION()
		virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp
			, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	virtual void Tick(float DeltaTime) override;

	void SetScale(const FVector& InputScale);
	void SetSpeed(const float& InputSpeed);

protected:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;
};
