// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEnemy.h"
#include "BaseCharacter.h"
#include "SpawnPoint.generated.h"

UCLASS()
class HAEWONPROJECT_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);
	UFUNCTION()
	void OnSpawn();

	UPROPERTY(EditDefaultsOnly, Category = "MyEnemy")
		UStaticMeshComponent* staticM;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* collisionSphere;

	UPROPERTY(EditAnywhere, Category = "MyEnemy")
		TSubclassOf<AMyEnemy>AtorToSpawn;

	UPROPERTY(EditAnywhere, Category = "MyEnemy")
		TArray<TSubclassOf<class AMyEnemy>>myEnemy;

private:
	float currentTime;
	bool isSpawn;

};
