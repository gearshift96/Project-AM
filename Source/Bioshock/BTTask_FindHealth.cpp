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

	AActor* Bot = OwnerComp.GetOwner();

	if (Bot)
	{
		FCollisionObjectQueryParams CollisionObjectParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic);

		FCollisionShape CollisionShape = FCollisionShape();
		CollisionShape.ShapeType = ECollisionShape::Sphere;
		CollisionShape.SetSphere(SearchRadius);

		TArray<FHitResult> OutHits;

		ABotController* BotCon = Cast<ABotController>(OwnerComp.GetAIOwner());

		/*DrawDebugSphere(GetWorld(), ((Bot->GetActorLocation() + FVector(150.f) - Bot->GetActorLocation()) / 2) + Bot->GetActorLocation(), SearchRadius, 10, FColor::Green, true);*/

		//Perform a Sphere Sweep with the according radius to find a nearby Ammo box
		if (GetWorld()->SweepMultiByObjectType(OutHits, Bot->GetActorLocation(), Bot->GetActorLocation() + FVector(150.f), FQuat(), CollisionObjectParams, CollisionShape) && BotCon)
		{
			for (int32 Hit = 0; Hit < OutHits.Num(); Hit++)
			{
				if (OutHits[Hit].GetActor() && Cast<AHealthPack>(OutHits[Hit].GetActor()))
				{
					//GLog->Log("found a health pack! updating location!");
					//DrawDebugPoint(GetWorld(), OutHits[Hit].ImpactPoint, 25.f, FColor::Black, true);
					AHealthPack* Pack = Cast<AHealthPack>(OutHits[Hit].GetActor());
					BotCon->SetHealthPack(Pack);

					return EBTNodeResult::Succeeded;
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}
