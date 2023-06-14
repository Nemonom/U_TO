#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class U_TO2_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();
	virtual void OnPossess(APawn* InPawn) override;

public:
	static const FName OriginPosKey;
	static const FName DestPosKey;
	static const FName TargetKey;

private:
	UPROPERTY()
		class UBehaviorTree* BehaviorTree;

	UPROPERTY()
		class UBlackboardData* BlackBoardData;
};
