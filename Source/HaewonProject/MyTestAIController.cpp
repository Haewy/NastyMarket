// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "MyTestCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
#include "Engine.h"
#include "blackboard_keys.h"
#include "UObject/UObjectGlobals.h"


AMyTestAIController::AMyTestAIController(FObjectInitializer const& object_initializer)
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>obj(TEXT("BehaviorTree'/Game/BP/AI/MyEnemy_BHVT.MyEnemy_BHVT'"));
	if (obj.Succeeded())
	{
		BHVT = obj.Object;
	}
	BHVTComp = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BbComp = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	//BHVTComp = object_initializer.CreateAbstractDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	//BbComp = object_initializer.CreateAbstractDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	SetupPerspectionSystem();

}

void AMyTestAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BHVT);
	BHVTComp->StartTree(*BHVT);


	//if (GetPerceptionComponent() != nullptr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("All System Set!"));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("There is no component..."));
	//}
}

void AMyTestAIController::OnPossess(APawn* ThisPawn)
{
	Super::OnPossess(ThisPawn);
	if (BbComp)
	{
		BbComp->InitializeBlackboard(*BHVT->BlackboardAsset);
	}
}

void AMyTestAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//AMyTestCharacter* ThisCharacter = Cast<AMyTestCharacter>(GetPawn());

	//if (IsPlayerDetected)
	//{
	//	AMyTestCharacter* Player = Cast<AMyTestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//	MoveToActor(Player, 5.f);
	//}
	//if (DistanceToPlayer > AISightRadius)
	//{
	//	IsPlayerDetected = false;
	//}

}

FRotator AMyTestAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.f, 0.f, 0.f);
	}
	return FRotator(0.f, GetPawn()->GetActorRotation().Yaw, 0.f);
}

void AMyTestAIController::OnTargetDetected(AActor* actor, FAIStimulus const stimulus)
{

	if(auto const ch = Cast<AMyTestCharacter>(actor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Find Player!!!!");
		GetBlackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());
	}
}

UBlackboardComponent* AMyTestAIController::GetBlackboard() const
{
	return BbComp;
}

//void AMyTestAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
//{
//	//for (size_t i = 0; i < DetectedPawns.Num(); i++)
//	//{
//	//	DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawns[i]);
//	//	UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), DistanceToPlayer);
//	//}
//	//IsPlayerDetected = true;
//	if (DetectedPawns.Num() > 0)
//	{
// 	   IsPlayerDetected = true;
//		UE_LOG(LogTemp, Warning, TEXT("Player is in the range!!!"));
//	}
//	else 
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Player is out...."));
//	}
//}

void AMyTestAIController::SetupPerspectionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = 500.0f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 50.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.f);

	SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMyTestAIController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);



}

