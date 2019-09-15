// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindAmmo.h"
#include "AICharacter.h"
#include "CollisionQueryParams.h"
#include "WorldCollision.h"
#include "Engine/World.h"
#include "AmmoBox.h"
#include "BotController.h"

EBTNodeResult::Type UBTTask_FindAmmo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Succeeded;

}
