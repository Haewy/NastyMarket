// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Engine/DataTable.h"
#include "MyTestCharacter.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FCharacterInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCharacterInfo()
	{
		characterName = FText::FromString("Name");
		characterLevel = 1;
		description = FText::FromString("Your Character is ....");
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName characterID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText characterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* characterThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 characterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText description;

};


UCLASS()
class HAEWONPROJECT_API AMyTestCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AMyTestCharacter();

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* FollowCamera;
	void BeginPlay();

	void Attack_Weapon();
	void Attack_Weapon_End();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInput)override;
	void MoveForward(float value);
	void MoveRight(float value);

private:
	class UAIPerceptionStimuliSourceComponent* stimulus;
	void SetStimulus();

};
