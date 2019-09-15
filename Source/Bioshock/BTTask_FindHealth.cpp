// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindHealth.h"
#include "AICharacter.h"
#include "CollisionQueryParams.h"
#include "WorldCollision.h"
#include "Engine/World.h"
#include "HealthPack.h"
#include "BotController.h"
//#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTTask_FindHealth::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Succeeded;
}
