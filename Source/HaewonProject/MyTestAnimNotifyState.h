// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyTestAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class HAEWONPROJECT_API UMyTestAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public: 
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float totalDuration)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
};
