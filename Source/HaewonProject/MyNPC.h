// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyNPC.generated.h"

UCLASS()
class HAEWONPROJECT_API AMyNPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyNPC();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere;

	bool isTalk;

	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f)override;

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* BotBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
		class USoundCue* InteractSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
