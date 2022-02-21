// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_RandomMove.h"
#include "HaewonProject.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "NavigationSystem.h"
#include "MyTestAIController.h"
#include "Engine.h"
#include "Engine/World.h"
#include "AIController.h"
#include "blackboard_keys.h"

UMyBTTask_RandomMove::UMyBTTask_RandomMove(FObjectInitializer const& object_initializer)
{
    NodeName = TEXT("Find Random Location");
}
EBTNodeResult::Type UMyBTTask_RandomMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    auto const cont = Cast<AMyTestAIController>(OwnerComp.GetAIOwner());
    auto const npc = cont->GetPawn();

    FVector const origin = npc->GetActorLocation();
    FNavLocation location;

    UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
    if (nav_sys->GetRandomPointInNavigableRadius(origin, search_radius, location, nullptr))
    {
        cont->GetBlackboard()->SetValueAsVector(bb_keys::target_location, location.Location);
    }

    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}
