// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CollectHealth.generated.h"

/**
 * Searches for nearby Health PAcks in the area and updates the corresponding Blackboard values
 * Should probably rename this later on since its name is misleading
 */
UCLASS()
class BIOSHOCK_API UBTTask_CollectHealth : public UBTTaskNode
{
	GENERATED_BODY()
	
	/*
	 * Executes the task when we have reached the node
	 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:

	/* The search radius the bot will try to find a health pack */
	UPROPERTY(EditAnywhere)
	float SearchRadius = 600.f;
};
