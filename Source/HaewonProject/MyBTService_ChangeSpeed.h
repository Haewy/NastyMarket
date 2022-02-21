// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_ChangeSpeed.generated.h"

/**
 * 
 */
UCLASS()
class HAEWONPROJECT_API UMyBTService_ChangeSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTService_ChangeSpeed();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

protected:
	FString GetStaticServiceDescription() const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float speed = 500.f;
	
};
