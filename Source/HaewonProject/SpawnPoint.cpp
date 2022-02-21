// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include "Engine.h"
#include "BaseCharacter.h"
#include "MyTestCharacter.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Containers/UnrealString.h"
#include "GameFramework/Actor.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isSpawn = false;
	collisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnPoint"));
	collisionSphere->InitSphereRadius(1000.f);
	RootComponent = collisionSphere;

	collisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASpawnPoint::OnOverlapBegin);
	collisionSphere->OnComponentEndOverlap.AddDynamic(this, &ASpawnPoint::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugSphere(GetWorld(), GetActorLocation(), 1000.f, 50, FColor::Green, true, -1, 0, 2);
	
}

// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isSpawn)
	{
		currentTime = currentTime + 1 * DeltaTime;

		if (currentTime >= 2.f)
		{
			FActorSpawnParameters spawnPrams;
			spawnPrams.Owner = this;
			spawnPrams.Instigator = Instigator;

			UWorld* WRLD = GetWorld();
			
			FVector location = GetActorLocation();
			FRotator rotation = GetActorRotation();

			int32 random = FMath::RandRange(0, myEnemy.Num());
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Random Number: %d"), random));

			for (int i = 0; i < myEnemy.Num(); ++i)
			{

				AMyEnemy* const myNewEnemy = WRLD->SpawnActor<AMyEnemy>(myEnemy[i], location, rotation);
			}


			currentTime = 0.f;
		}
	}
}

void ASpawnPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMyTestCharacter::StaticClass()))
	{
		if (!isSpawn)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Player is in SpawnPoint !"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Number of Enemy: %d"), myEnemy.Num()));
			isSpawn = true;
		}
	}
}

void ASpawnPoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AMyTestCharacter::StaticClass()))
	{
		if (isSpawn)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Player is out from SpawnPoint..."));
			isSpawn = false;
		}
	}
}

void ASpawnPoint::OnSpawn()
{

}

