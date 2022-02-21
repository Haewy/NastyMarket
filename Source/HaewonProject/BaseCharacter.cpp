// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Animation/AnimInstance.h"
#include "Containers/Array.h"
#include "MyWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AISense_Sight.h"
//#include "GameFramework/Character.h"
#include "Engine.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isAttacking = false; 
	isDead = false;
	attack_Number = 0;

	hp = 0.f;
	maxHp = 100.f;

	hp = maxHp;
}

//========================== W E A P O N =====================
USkeletalMeshComponent* ABaseCharacter::GetSpecificPawnMesh() const
{
	return GetMesh();
}
FName ABaseCharacter::GetWeaponAttachPoint() const
{
	return  WeaponAttachPoint;
}

void ABaseCharacter::EquipWeapon(AMyWeapon* Weapon)
{
	if (Weapon)
	{
		SetCurrentWeapon(Weapon, CurrentWeapon);
	}
}

void ABaseCharacter::OnChangeWeapon()
{
	const int32 currentWeaponIndex = Inventory.IndexOfByKey(CurrentWeapon);
	
	if (currentWeaponIndex < Inventory.Num())
	{
		FActorSpawnParameters SpawnInfo;
		UWorld* world = GetWorld();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Current Index: %d"), currentWeaponIndex));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Inventory: %d"), Inventory.Num()));
		//for (int32 i = 0; i < Inventory.Num(); i++)
		//{
		//	if (currentWeaponIndex == i)
		//	{

		//		//AMyWeapon* NextWeapon = Inventory[(currentWeaponIndex + 1)]; // Error
		//		AMyWeapon* NextWeapon = world->SpawnActor<AMyWeapon>(DefaultInventoryClasses[1], SpawnInfo);
		//		NextWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightHandSocket"));
		//	}
		//	else
		//	{
		//		//AMyWeapon* NextWeapon = Inventory[0]; // Error
		//		AMyWeapon* NextWeapon = world->SpawnActor<AMyWeapon>(DefaultInventoryClasses[0], SpawnInfo);
		//		NextWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightHandSocket"));
		//	}
		//}

	}
	
	//AMyWeapon* NextWeapon = Inventory[(currentWeaponIndex + 1)]; // Error
	
	//EquipWeapon(NextWeapon);
}

void ABaseCharacter::WeaponAttack()
{
	CurrentWeapon->StartAttack();
}
void ABaseCharacter::AddWeapon(AMyWeapon* Weapon)
{
	if (Weapon)
	{
		Inventory.AddUnique(Weapon);
	}
}

void ABaseCharacter::SetCurrentWeapon(AMyWeapon* NewWeapon, AMyWeapon* LastWeapon)
{
	AMyWeapon* LocalLastWeapon = NULL;
	if (LastWeapon != NULL)
	{
		LocalLastWeapon = LastWeapon;
	}
	else if (NewWeapon != CurrentWeapon)
	{
		LocalLastWeapon = CurrentWeapon;
	}

	if (LocalLastWeapon)
	{
		LocalLastWeapon->OnUnequip();
	}

	CurrentWeapon = NewWeapon;

	if (NewWeapon)
	{
		NewWeapon->SetOwningPawn(this);
		NewWeapon->OnEquip(LastWeapon);
	}

}
void ABaseCharacter::SpawnDefaultInventory()
{
	int32 NumWeaponClasses = DefaultInventoryClasses.Num();


	for (int32 i = 0; i < NumWeaponClasses; i++)
	{
		if (DefaultInventoryClasses[i])
		{
			FActorSpawnParameters SpawnInfo;
			UWorld* world = GetWorld();
			AMyWeapon* NewWeapon_Inventory = world->SpawnActor<AMyWeapon>(DefaultInventoryClasses[i], SpawnInfo);
			NewWeapon_Inventory->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightHandSocket"));
			AddWeapon(NewWeapon_Inventory);
		}
	}

	if (Inventory.Num() > 0)
	{
		EquipWeapon(Inventory[0]);
	}

}
//=====================================================


// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::Attack()
{

	isAttacking = true;

	if (attack_Number < 3)
	{
		int temp_Num = rand() % 3 + 1;
		FString PlaySection = "Attack_" + FString::FromInt(temp_Num);
		PlayAnimMontage(Attack_AnimM, 1.f, FName(*PlaySection));
		//attack_Number++;

		isAttacking = false;
	}
	else
	{
		//PlayAnimMontage(AttackEnd_Anims, 1.f, FName("Attack_4"));
		attack_Number = 0;
		isAttacking = false;
	}
	

}
void ABaseCharacter::Attack_End()
{
	isAttacking = false;

}

void ABaseCharacter::DeathAnimEnd()
{
	this->SetActorHiddenInGame(true);
	SetLifeSpan(0.1f);
}

void ABaseCharacter::OnHit(float Damage, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	PlayAnimMontage(Hit_AnimM, 1.0f);
	if (Damage > 0.f)
	{
		ApplyDamageMomentum(Damage, DamageEvent, PawnInstigator, DamageCauser);
	}
}

float ABaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	PlayAnimMontage(Hit_AnimM);
	const float myTakeDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (hp > 0.f)
	{
		hp -= myTakeDamage;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("HP is: %f"), hp));
		OnHit(myTakeDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
	}
	if (hp <= 0)
	{
		//this->Destroy();
		OnDeath(myTakeDamage, DamageEvent, EventInstigator, DamageCauser);
	}

	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("HP is: %f"), hp));
	//	hp -= myTakeDamage;
	//	OnHit(myTakeDamage, DamageEvent, EventInstigator? EventInstigator->GetPawn() : NULL, DamageCauser);
	//}
	PlayAnimMontage(Hit_AnimM, 1.0f);
	return 0.0f;
}

void ABaseCharacter::OnDeath(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	isDead = true;

	hp = FMath::Min(0.0f, hp);
	
	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();
	
	EventInstigator = GetDamageInstigator(EventInstigator, *DamageType);

	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}
	if (Controller)
	{
		Controller->Destroy();
	}
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetSimulatePhysics(true);

	float deathAnimMDuration = PlayAnimMontage(Death_AnimM);

	FTimerHandle TimeHandle;
	GetWorldTimerManager().SetTimer(TimeHandle, this, &ABaseCharacter::DeathAnimEnd, deathAnimMDuration, false);


}

