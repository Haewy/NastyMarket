// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPC.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine.h"
#include "MyTestCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyNPC::AMyNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GateCollisionSphere"));
	CollisionSphere->SetupAttachment(this->GetCapsuleComponent());
	CollisionSphere->InitSphereRadius(250.0f);


	isTalk = false;

}

void AMyNPC::FaceRotation(FRotator NewRotation, float DeltaTime)
{

	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);
	Super::FaceRotation(CurrentRotation, DeltaTime);
}

// Called when the game starts or when spawned
void AMyNPC::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMyNPC::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AMyNPC::OnOverlapEnd);
}

// Called every frame
void AMyNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector PlayerPos = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
	FVector myLocation = GetActorLocation();

	FVector Forward = (PlayerPos - myLocation);

	FRotator PlayerRot = FRotationMatrix::MakeFromX(Forward).Rotator();

	if (isTalk)
	{
		FaceRotation(PlayerRot, 0.01f);

	}
	else
	{
		//FaceRotation(PlayerRot, 0.f);
	}
}

void AMyNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && !isTalk)
	{

		UGameplayStatics::PlaySound2D(this, InteractSound);
		isTalk = true;

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("Touch!!"));


	}
}

void AMyNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && isTalk)
	{
		//isTalk = false;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("Out!"));
	}
}


