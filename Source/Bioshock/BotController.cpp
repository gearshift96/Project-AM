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
#include "PlayerCharacter.h"
#include "ExplosiveHazard.h"

ABotController::ABotController()
{
	//Keys init
	BlackboardKey_ShouldRetreat = FName("ShouldRetreat");
	BlackboardKey_CollectAmmo = FName("CollectAmmo");
	BlackboardKey_AmmoBox = FName("AmmoBox");
	BlackboardKey_CollectHealth = FName("CollectHealth");
	BlackboardKey_HealthPack = FName("HealthPack");


}

void ABotController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void ABotController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABotController::BeginPlay()
{
	Super::BeginPlay();

}

void ABotController::OnUnPossess()
{
	Super::OnUnPossess();

	//By default the controller will stay in the level so manually destroy this actor
	Destroy();
}
