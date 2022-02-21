// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ChasePlayer.h"
#include "MyTestAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "blackboard_keys.h"

UMyBTTask_ChasePlayer::UMyBTTask_ChasePlayer(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Chase Player");
}
EBTNodeResult::Type UMyBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyTestAIController* const cont = Cast<AMyTestAIController>(OwnerComp.GetAIOwner());
	FVector const player_location = cont->GetBlackboard()->GetValueAsVector(bb_keys::target_location);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, player_location);


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}
