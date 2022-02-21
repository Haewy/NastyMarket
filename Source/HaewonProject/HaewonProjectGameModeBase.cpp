// Copyright Epic Games, Inc. All Rights Reserved.


#include "HaewonProjectGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AHaewonProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	currentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	currentWidget->AddToViewport();
}

