// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

AMyTestCharacter::AMyTestCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 700.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

}

void AMyTestCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SpawnDefaultInventory();
}



void AMyTestCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyTestCharacter::Attack_Weapon()
{
	if (!isAttacking)
	{
		if (attack_Number < 3)
		{
			int tmp_Num = rand() % 3 + 1;
			FString PlaySection = "Attack_" + FString::FromInt(tmp_Num);
			PlayAnimMontage(Attack_AnimM, 1.0f, FName(*PlaySection));
			attack_Number++;
			isAttacking = true;

		}
		else
		{
			PlayAnimMontage(Attack_AnimM, 1.0f, FName("Attack_4"));
			attack_Number = 0;
		}
	}
}

void AMyTestCharacter::Attack_Weapon_End()
{
	isAttacking = false;
}

void AMyTestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInput)
{
	check(PlayerInput);
	PlayerInput->BindAxis("MoveForward", this, &AMyTestCharacter::MoveForward);
	PlayerInput->BindAxis("MoveRight", this, &AMyTestCharacter::MoveRight);

	PlayerInput->BindAction("Attack", IE_Released, this, &AMyTestCharacter::Attack);

	PlayerInput->BindAction("ChangeWeapon", IE_Released, this, &ABaseCharacter::OnChangeWeapon);
}
void AMyTestCharacter::MoveForward(float value)
{
	if ((Controller != NULL) && (value !=0.0f) && isAttacking==false)
	{
		const FRotator rotator = Controller->GetControlRotation();
		const FRotator yawRotator(0, rotator.Yaw, 0);
		const FVector direction = FRotationMatrix(yawRotator).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, value);
		
		attack_Number = 0;
	}

}
void AMyTestCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f) && !(isAttacking))
	{
		const FRotator rotator = Controller->GetControlRotation();
		const FRotator yawRotator(0, rotator.Yaw, 0);
		const FVector direction = FRotationMatrix(yawRotator).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, value);

		attack_Number = 0;
	}
}

void AMyTestCharacter::SetStimulus()
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}
