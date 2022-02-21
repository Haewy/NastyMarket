// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectile.h"
#include "Components/SphereComponent.h"
#include "BaseCharacter.h"
#include "MyTestCharacter.h"
#include "Engine.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMyProjectile::AMyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(10.0f);
	CollisionComp->SetCollisionProfileName("Peasant_Projectile");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMyProjectile::OnOverlapBegin);
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	InitialLifeSpan = 3.0f;

}


void AMyProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFormSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->IsA(AMyTestCharacter::StaticClass()))
		{
			UGameplayStatics::ApplyDamage(OtherActor, 5.0f, NULL, this, UDamageType::StaticClass());
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("IT IS THE PLAYER ! Projectile damages on it !!!"));
			Destroy();

		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("It is the player. Do not apply damage..."));
			Destroy();
		}
	}
}

void AMyProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NomalImpulse, const FHitResult& Hit)
{
}

void AMyProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && (OtherActor != this))
	{
		Destroy();
		if (OtherActor->IsA(ABaseCharacter::StaticClass()))
		{
			UGameplayStatics::ApplyDamage(OtherActor, 10.0f, NULL, this, UDamageType::StaticClass());
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, __FUNCTION__);
		}

	}
}
