// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCharacter.h" 
#include "MyTestCharacter.h" 
#include "MyWeapon.generated.h"

UCLASS()
class HAEWONPROJECT_API AMyWeapon : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		UStaticMeshComponent* WeaponMesh;//USkeletalMeshComponent* WeaponMesh;//

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
	class UBoxComponent* WeaponCollision;

	bool isWeaponAttacking;
public:	
	// Sets default values for this actor's properties
	AMyWeapon(const class FObjectInitializer& ObjectInitializer);

	void SetOwningPawn(ABaseCharacter* NewOwner);
	void AttachMeshToPawn();
	void OnEquip(const AMyWeapon* LastWeapon);
	void OnUnequip();
	void StartAttack();
	void StopAttack();

	//UFUNCTION()
	//void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	//		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFormSweep,
			const FHitResult& SweepResult);

protected:
	class ABaseCharacter* MyPawn;
	virtual void BeginPlay();

public: 
	virtual void Tick(float DeltaTime)override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override; // Get crash


};
