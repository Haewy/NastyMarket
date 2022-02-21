// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HaewonProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HAEWONPROJECT_API AHaewonProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay()override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	UUserWidget* currentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	// To restrain only UUserWidget... 
	TSubclassOf<UUserWidget> HUDWidget;
	
};
