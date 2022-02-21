// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Animation/AnimMontage.h"
#include "CombatInterface.h"
#include "MyEnemy.generated.h"

/**
 * 
 */
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class HAEWONPROJECT_API AMyEnemy : public ABaseCharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	AMyEnemy();

	FName GetBulletPoint() const;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FName MyEnemyName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		class USphereComponent* WeaponCollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FName BulletPoint; 	//RightHandIndex4

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		TSubclassOf<class AMyProjectile> MyBullet;

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* EnemyBHVT;

	UPROPERTY(EditAnywhere, Category = Behavior)
		UAnimMontage* Attack;

	virtual int melee_attack_Implementation()override;

	UAnimMontage* get_montage() const;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* montage;

};
