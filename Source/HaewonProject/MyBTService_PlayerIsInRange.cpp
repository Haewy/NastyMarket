// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_PlayerIsInRange.h"
#include "MyEnemy.h"
#include "MyTestAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


UMyBTService_PlayerIsInRange::UMyBTService_PlayerIsInRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player in Attack Range");
}
void UMyBTService_PlayerIsInRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	AMyTestAIController* const cont = Cast<AMyTestAIController>(OwnerComp.GetAIOwner());
	AMyEnemy* const npcEnemy = Cast<AMyEnemy>(cont->GetPawn());

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	cont->GetBlackboard()->SetValueAsBool(bb_keys::player_is_in_AttackRange, npcEnemy->GetDistanceTo(player) <= Attack_range);
}
