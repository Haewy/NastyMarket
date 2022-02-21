// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_PlayerIsInRange.generated.h"

/**
 * 
 */
UCLASS()
class HAEWONPROJECT_API UMyBTService_PlayerIsInRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTService_PlayerIsInRange();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float Attack_range = 30.0f;
	
};
