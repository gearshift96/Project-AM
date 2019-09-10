// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckForHealth.generated.h"

/**
* This service checks if the Bot need Health.
* If that's the case it updates the corresponding Blackboard Values
*/
UCLASS()
class BIOSHOCK_API UBTService_CheckForHealth : public UBTService
{
	GENERATED_BODY()

	/*
	 * Executed every tick interval (which you can set from the Behavior Tree while have this particular service selected)
	 */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
