// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindPlayerLocation.h"
//#include "MyTestGame.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem.h"
#include "MyTestAIController.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "blackboard_keys.h"

UMyBTTask_FindPlayerLocation::UMyBTTask_FindPlayerLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Player Location");
}
EBTNodeResult::Type UMyBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const cont = Cast<AMyTestAIController>(OwnerComp.GetAIOwner());

	FVector const player_location = player->GetActorLocation();

	if (search_random)
	{
		FNavLocation location;

		UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());

		if (nav_sys->GetRandomPointInNavigableRadius(player_location, search_radius, location, nullptr))
		{
			cont->GetBlackboard()->SetValueAsVector(bb_keys::target_location, location.Location);
		}
	}
	else
	{
		cont->GetBlackboard()->SetValueAsVector(bb_keys::target_location, player_location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
