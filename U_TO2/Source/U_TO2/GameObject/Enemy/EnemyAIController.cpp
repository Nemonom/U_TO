#include "EnemyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

const FName AEnemyAIController::OriginPosKey(TEXT("OriginPos"));
const FName AEnemyAIController::DestPosKey(TEXT("DestPos"));
const FName AEnemyAIController::TargetKey(TEXT("Target"));

AEnemyAIController::AEnemyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackBoardObject(TEXT("/Game/Book/AI/EnemyBlackBoard.EnemyBlackBoard"));
	if (BlackBoardObject.Succeeded())
	{
		BlackBoardData = BlackBoardObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObject(TEXT("/Game/Book/AI/EnemyBehaviorTree.EnemyBehaviorTree"));
	if (BehaviorTreeObject.Succeeded())
	{
		BehaviorTree = BehaviorTreeObject.Object;
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (UseBlackboard(BlackBoardData, Blackboard))
	{
		Blackboard->SetValueAsVector(OriginPosKey, InPawn->GetActorLocation());

		if (!RunBehaviorTree(BehaviorTree))
			UE_LOG(LogTemp, Warning, TEXT("Couldn't run behavior tree"));
	}
}
