// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTestActor.generated.h"

UCLASS()
class HAEWONPROJECT_API AMyTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
		UParticleSystem* particles;
	
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent*OverlappedComp, AActor*OtherActor, UPrimitiveComponent*OtherComp, 
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;

};
