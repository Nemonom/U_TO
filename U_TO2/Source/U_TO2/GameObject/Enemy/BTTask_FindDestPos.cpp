// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindDestPos.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindDestPos::UBTTask_FindDestPos()
{
	NodeName = TEXT("FindDestPos");
}

EBTNodeResult::Type UBTTask_FindDestPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AEnemyAIController::OriginPosKey);
	FVector NextPatrol{ Origin.X + rand() % 500, Origin.Y + rand() % 500, 120.f };

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::DestPosKey, NextPatrol);


	return EBTNodeResult::Succeeded;
}
