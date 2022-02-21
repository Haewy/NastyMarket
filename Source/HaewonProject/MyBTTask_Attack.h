// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyEnemy.h"
#include "MyBTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class HAEWONPROJECT_API UMyBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTTask_Attack(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

private:
	bool montage_has_finished(AMyEnemy* const npcEnemy);
};
