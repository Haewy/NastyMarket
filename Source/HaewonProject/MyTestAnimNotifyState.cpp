// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestAnimNotifyState.h"
#include "Engine.h"
#include "BaseCharacter.h"


void UMyTestAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float totalDuration)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, __FUNCTION__);

	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		ABaseCharacter* Player = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->isAttacking = true;
		}
	}
}
void UMyTestAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, __FUNCTION__);

	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		ABaseCharacter* Player = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->Attack_End();
			Player->isAttacking = false;
		}
	}
}