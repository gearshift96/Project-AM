// Fill out your copyright notice in the Description page of Project Settings.


#include "BotController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "AICharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "BotPathFollowingComponent.h"
#include "AmmoBox.h"
#include "HealthPack.h"

ABotController::ABotController()
{
	//Keys init
	BlackboardKey_MoveLocation = FName("MoveLocation");
	BlackboardKey_SelectedTarget = FName("SelectedTarget");
	BlackboardKey_ShouldRetreat = FName("ShouldRetreat");
	BlackboardKey_CollectAmmo = FName("CollectAmmo");
	BlackboardKey_AmmoBox = FName("AmmoBox");
	BlackboardKey_CollectHealth = FName("CollectHealth");
	BlackboardKey_HealthPack = FName("HealthPack");

	//Create the AI perception component
	if (!GetPerceptionComponent())
	{
		PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(FName("PawnSensingComp"));

		if (PerceptionComp)
		{
			SetPerceptionComponent(*PerceptionComp);
		}
	}

	//Initialise our custom path following comp. In beginplay make it as the default comp for our character's path following comp
	BotPathFollowingComp = CreateDefaultSubobject<UBotPathFollowingComponent>(FName("BotPathFollowingComponent"));
}

FVector ABotController::GetSelectedTargetLocation() const
{
	const UBlackboardComponent* BlackBoardComp = GetBlackboardComponent();
	if (BlackBoardComp)
	{
		UObject* Target = BlackBoardComp->GetValueAsObject(BlackboardKey_SelectedTarget);

		if (!Target) return FVector::ForwardVector;

		AActor* SelectedTarget = Cast<AActor>(Target);
		if (SelectedTarget)
		{
			return SelectedTarget->GetActorLocation();
		}
	}

	return FVector::ForwardVector;
}

void ABotController::SetMoveToLocation(const FVector& Location)
{
	ensure(GetBlackboardComponent());
	GetBlackboardComponent()->SetValueAsVector(BlackboardKey_MoveLocation, Location);
}

void ABotController::SetAmmoBox(AAmmoBox* AmmoBox)
{
	ensure(GetBlackboardComponent());
	GetBlackboardComponent()->SetValueAsObject(BlackboardKey_AmmoBox, AmmoBox);
}

void ABotController::SetHealthPack(AHealthPack * HealthPack)
{
	ensure(GetBlackboardComponent());
	GetBlackboardComponent()->SetValueAsObject(BlackboardKey_HealthPack, HealthPack);
}

void ABotController::InitiateRetreat()
{
	ensure(GetBlackboardComponent());
	GetBlackboardComponent()->SetValueAsBool(BlackboardKey_ShouldRetreat, true);
}

void ABotController::SetCollectAmmoStatus(const bool& NewStatus)
{
	ensure(GetBlackboardComponent());
	GetBlackboardComponent()->SetValueAsBool(BlackboardKey_CollectAmmo, NewStatus);
}

void ABotController::SetCollectHealthStatus(const bool & NewStatus)
{
	ensure(GetBlackboardComponent());
	GetBlackboardComponent()->SetValueAsBool(BlackboardKey_CollectHealth, NewStatus);
}

void ABotController::SelectTarget(const TArray<AActor*>& TargetList)
{

}

void ABotController::OnPerceptionUpdated(const TArray<AActor*>& SensedActors)
{
	SelectTarget(SensedActors);

}

AActor* ABotController::GetSelectedTarget() const
{
	if (GetBlackboardComponent())
	{
		UObject* Target = GetBlackboardComponent()->GetValueAsObject(BlackboardKey_SelectedTarget);
		if (Target)
		{
			return Cast<AActor>(Target);
		}
	}
	return nullptr;
}

void ABotController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!BTAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid BT Asset"));
		return;
	}
}

void ABotController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABotController::BeginPlay()
{
	Super::BeginPlay();

	if (BotPathFollowingComp)
	{
		//For some reason this works fine inside begin play and not in the constructor.
		SetPathFollowingComponent(BotPathFollowingComp);
	}
}

void ABotController::OnUnPossess()
{
	Super::OnUnPossess();

	//By default the controller will stay in the level so manually destroy this actor
	Destroy();
}
