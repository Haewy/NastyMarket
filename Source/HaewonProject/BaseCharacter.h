// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class HAEWONPROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
	FName MyCharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health)
	float hp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health)
	float maxHp;

	USkeletalMeshComponent* GetSpecificPawnMesh() const;

	FName GetWeaponAttachPoint() const;

	void EquipWeapon(class AMyWeapon* Weapon);
	void OnChangeWeapon();
	void WeaponAttack();


protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	FName WeaponAttachPoint;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TArray<TSubclassOf<class AMyWeapon>>DefaultInventoryClasses;

	TArray<class AMyWeapon*>Inventory;

	class AMyWeapon* CurrentWeapon;

	void AddWeapon(class AMyWeapon* Weapon);

	void SetCurrentWeapon(class AMyWeapon* NewWeapon, class AMyWeapon* LastWeapon);

	void SpawnDefaultInventory();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void Attack();
	void Attack_End();
	void DeathAnimEnd();
	
	virtual void OnHit(float Damage, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController*EventInstigator, AActor*DamageCauser);
	virtual void OnDeath(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* Attack_AnimM;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* Hit_AnimM;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* Death_AnimM;

	//UPROPERTY(EditDefaultsOnly, Category = Pawn)
	//UAnimMontage* AttackEnd_Anims;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyState")
	bool isAttacking;
	bool isDead = false;
	int32 attack_Number;


};
