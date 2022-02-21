// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Attack.h"
#include "MyTestAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "AIController.h"
#include "BaseCharacter.h"
#include "MyEnemy.h"
#include "CombatInterface.h"


UMyBTTask_Attack::UMyBTTask_Attack(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Attack");
}
EBTNodeResult::Type UMyBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const cont = OwnerComp.GetAIOwner();
	AMyEnemy* const npcEnemy = Cast<AMyEnemy>(cont->GetPawn());

	if (ICombatInterface* const icombat = Cast<ICombatInterface>(npcEnemy))
	{
		if (montage_has_finished(npcEnemy))
		{
			icombat->Execute_melee_attack(npcEnemy);
		}
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UMyBTTask_Attack::montage_has_finished(AMyEnemy* const npcEnemy)
{
	return npcEnemy->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npcEnemy->get_montage());
}
