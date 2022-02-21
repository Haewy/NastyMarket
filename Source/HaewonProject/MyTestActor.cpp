// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "MyTestCharacter.h"
#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyTestActor::AMyTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obj"));
	RootComponent = StaticMesh;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->InitSphereRadius(100.0f);
	CollisionSphere->SetupAttachment(StaticMesh);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMyTestActor::OnOverlapBegin);

	static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	particles = ParticleAsset.Object;

}

// Called when the game starts or when spawned
void AMyTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AMyTestActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMyTestCharacter::StaticClass()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Collistion Works!!!!!!!"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Apply Damage!!!!!!"));
		UGameplayStatics::ApplyDamage(OtherActor, 50.f, NULL, this, UDamageType::StaticClass());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particles, GetActorLocation());

		Destroy();
	}
}
//void AMyTestActor::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	if (OtherActor->IsA(AMyTestCharacter::StaticClass()))
//	{
//		UGameplayStatics::ApplyDamage(OtherActor, 50.f, NULL, this, UDamageType::StaticClass());
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Apply Damage!!!!!!"));
//	}
//}

