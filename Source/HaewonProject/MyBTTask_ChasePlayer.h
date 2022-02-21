// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "MyEnemy.h"
#include "MyBTTask_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class HAEWONPROJECT_API UMyBTTask_ChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTTask_ChasePlayer(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	
};
