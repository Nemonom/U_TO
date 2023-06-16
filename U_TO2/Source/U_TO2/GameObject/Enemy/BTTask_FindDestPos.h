// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindDestPos.generated.h"

/**
 * 
 */
UCLASS()
class U_TO2_API UBTTask_FindDestPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindDestPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
