// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_ChangeSpeed.h"
#include "MyEnemy.h"
#include "MyTestAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UMyBTService_ChangeSpeed::UMyBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
}
void UMyBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	auto const cont = OwnerComp.GetAIOwner();
	AMyEnemy* const npcEnemy = Cast<AMyEnemy>(cont->GetPawn());
	npcEnemy->GetCharacterMovement()->MaxWalkSpeed = speed;
}

FString UMyBTService_ChangeSpeed::GetStaticServiceDescription() const
{
	return FString("Change the Enemy walking speed faster!");
}
