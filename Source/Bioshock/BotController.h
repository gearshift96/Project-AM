// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BotController.generated.h"

/**
 * 
 */
UCLASS()
class BIOSHOCK_API ABotController : public AAIController
{
	GENERATED_BODY()

	private:

	/* Time in seconds in which the target selection occured */
	float TimeSinceTargetSelection;

public:

	ABotController();

protected:

	/* Blackboard key for MoveLocation*/
	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_MoveLocation;

	/* Blackboard key for Selected Target*/
	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_SelectedTarget;

	/* Blackboard key for Should Retreat*/
	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_ShouldRetreat;

	/* Blackboard key for CollectAmmo */
	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_CollectAmmo;

	/* Blackboard key for Ammo Box Reference*/
	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_AmmoBox;

	/* Blackboard key for HealthPack */
	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_CollectHealth;

	/* Blackboard key for Health Pack Reference*/
	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_HealthPack;

	/* Will only select target every X interval */
	UPROPERTY(EditDefaultsOnly)
	float SelectTargetInterval = 5.f;

	/* How fast the bot rotates to face a new target */
	UPROPERTY(EditAnywhere)
	float SelectTargetRotationSpeed = 1.f;

	/* The Perception component for this controller */
	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionComponent* PerceptionComp;

	/* Should probably erase this on next iteration since its not used currently */
	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionStimuliSourceComponent* StimuliSourceComp;

	/* The custom path following component */
	UPROPERTY(VisibleAnywhere)
	class UBotPathFollowingComponent* BotPathFollowingComp;

	/* Executes when we possess a new bot */
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void OnUnPossess() override;
};
