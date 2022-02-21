// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MyTestAIController.generated.h"

/**
 * 
 */
class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS() // (config=Game)
class AMyTestAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyTestAIController(FObjectInitializer const& object_intializer = FObjectInitializer::Get());

	virtual void BeginPlay()override;
	virtual void OnPossess(APawn* Pawn)override;
	virtual void Tick(float DeltaSeconds)override;
	virtual FRotator GetControlRotation()const override;

	UFUNCTION(BlueprintCallable, Category = Behavior)
		void OnTargetDetected(AActor* actor, FAIStimulus const stimulus);

	class UBlackboardComponent* GetBlackboard() const;
	//UFUNCTION()
	//void OnPawnDetected(const TArray<AActor*> &DetectedPawns);


	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	//	float AISightRadius = 500.f;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	//	float AISightAge = 5.f;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	//	float AILoseSightRadius = AISightRadius + 50.f;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	//	float AIFieldOfView = 90.f;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	//	class UAISenseConfig_Sight* SightConfig;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	//	bool IsPlayerDetected = false;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	//float DistanceToPlayer = 0.0f;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* BHVTComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BHVT;

	class UBlackboardComponent* BbComp;
	class UAISenseConfig_Sight* SightConfig;

	void SetupPerspectionSystem();





	
};
