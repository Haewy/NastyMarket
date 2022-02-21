// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyProjectile.h"
#include "Engine/World.h"
#include "MyTestCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Engine.h"

AMyEnemy::AMyEnemy()
{
	WeaponCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("WeaponCollisionSphere"));
	WeaponCollisionSphere->InitSphereRadius(30.0f);
	WeaponCollisionSphere->AttachTo(GetMesh(), "WeaponPoint");

	GetCharacterMovement()->bOrientRotationToMovement = true;



}

FName AMyEnemy::GetBulletPoint() const
{
	return BulletPoint;
}

void AMyEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(AMyTestCharacter::StaticClass()) && PlayAnimMontage(montage) > 0.2f)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, NULL, this, UDamageType::StaticClass());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Enemy is hitting the player with his weapon! "));

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Enemy is hitting NOTHING with his weapon...."));
	}
}

int AMyEnemy::melee_attack_Implementation()
{
	if (montage)
	{
		PlayAnimMontage(montage);

		if (MyEnemyName == "Peasant" && MyBullet)
		{
			const FRotator SpawnRotation = GetActorRotation();
			const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FVector(80.f, 30.f, 10.f));
			//const FVector SpawnLocation = GetSpecificPawnMesh()->GetBoneLocation(FName("RightHandIndex4"));//= GetActorLocation() + SpawnRotation.RotateVector(FVector(80.f,30.f,10.f));
			//const FRotator SpawnRotation = GetActorRotation();
			UWorld* const World = GetWorld();
			
			if (World != NULL)
			{
				World->SpawnActor<AMyProjectile>(MyBullet, SpawnLocation, SpawnRotation);
				
			}
		}
	}
	return 0;
}

UAnimMontage* AMyEnemy::get_montage() const
{
	return montage;
}
