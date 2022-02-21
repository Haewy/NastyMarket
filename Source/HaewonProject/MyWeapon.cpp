 // Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "MyTestCharacter.h"
#include "BaseCharacter.h"
#include "MyEnemy.h"

// Sets default values
AMyWeapon::AMyWeapon(const class FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,TEXT("Weapon")); //CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	
	WeaponMesh->CastShadow = true;
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMesh;

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetBoxExtent(FVector(3.f, 3.f, 3.f));
	WeaponCollision->SetupAttachment(WeaponMesh);
	WeaponCollision->AttachTo(WeaponMesh);

	isWeaponAttacking = false;

	//WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
	//WeaponMesh->CastShadow = true;
	//WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//RootComponent = WeaponMesh;

	//WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollsion"));
	//WeaponCollision->SetBoxExtent(FVector(5.0f, 5.0f, 5.0f));
	//WeaponCollision->AttachTo(WeaponMesh, "RightHandSocket");


	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyWeapon::OnOverlapBegin);

}
void AMyWeapon::SetOwningPawn(ABaseCharacter* NewOwner)
{
	if (MyPawn != NewOwner)
	{
		MyPawn = NewOwner;
	}
}
void AMyWeapon::AttachMeshToPawn()
{
	if (MyPawn)
	{
		USkeletalMeshComponent* PawnMesh = MyPawn->GetSpecificPawnMesh();
		FName AttachPoint = MyPawn->GetWeaponAttachPoint();
		WeaponMesh->SetHiddenInGame(false);
		WeaponMesh->AttachTo(PawnMesh, AttachPoint, EAttachLocation::SnapToTarget); // Error!!!!!!!!!!!!
		

	}
}
void AMyWeapon::OnEquip(const AMyWeapon* LastWeapon)
{
	//AttachMeshToPawn();
	//WeaponMesh->SetHiddenInGame(false); //Error !!!!!!!!!!!!!!!!!
}

void AMyWeapon::OnUnequip()
{
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	WeaponMesh->SetHiddenInGame(true);
}

void AMyWeapon::StartAttack()
{
	isWeaponAttacking = true;
}

void AMyWeapon::StopAttack()
{
	isWeaponAttacking = false;
}



void AMyWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFormSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->IsA(AMyEnemy::StaticClass()))
		{
			UGameplayStatics::ApplyDamage(OtherActor, 50.0f, NULL, this, UDamageType::StaticClass());
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("IT IS THE ENEMY ! Weapon is working !!!"));

		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("It is nothing. Do not apply damage..."));
		}
	}

}

void AMyWeapon::BeginPlay()
{
	//AttachMeshToPawn();
}



void AMyWeapon::Tick(float DeltaTime)
{
}

void AMyWeapon::NotifyActorBeginOverlap(AActor* OtherActor) // Here does not work...
{

	Super::NotifyActorBeginOverlap(OtherActor);

	AMyEnemy* MyEnemy = Cast<AMyEnemy>(OtherActor);

	if (IsValid == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "nullptr");
	}
	else
	{
		//OtherActor->IsA(AActor::StaticClass()) && isWeaponAttacking == true && OtherActor == MyEnemy
		if (OtherActor->IsA(AActor::StaticClass()) && isWeaponAttacking == true && OtherActor == MyEnemy) 
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap is working, this is ENEMY !!!"));
			UGameplayStatics::ApplyDamage(OtherActor, 50.0f, NULL, this, UDamageType::StaticClass());
			isWeaponAttacking = false;

			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, __FUNCTION__);
		}
	}
}


