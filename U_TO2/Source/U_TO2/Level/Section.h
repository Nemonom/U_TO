#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Common/U_TOCommon.h"
#include "Section.generated.h"

UCLASS()
class U_TO2_API ASection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetState(ESectionState NewState);

	void OperateGates(bool bOpen = true);

	UFUNCTION()
		void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
		TArray<UStaticMeshComponent*> GateMeshes;

	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Trigger, Meta = (AllowPrivateAccess = true))
		TArray<UBoxComponent*> GateTriggers;

	UPROPERTY(VisibleAnywhere, Category = Trigger, Meta = (AllowPrivateAccess = true))
		UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, Category = State, Meta = (AllowPrivateAccess = true))
		bool IsBattleSection{ false };

	ESectionState CurrentState{ ESectionState::READY };
};
