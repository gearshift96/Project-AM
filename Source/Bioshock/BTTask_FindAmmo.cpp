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
				if (OutHits[Hit].GetActor() && Cast<AAmmoBox>(OutHits[Hit].GetActor()))
				{
					//GLog->Log("found an ammo box! updating location!");
					//DrawDebugPoint(GetWorld(), OutHits[Hit].ImpactPoint, 25.f, FColor::Black, true);
					AAmmoBox* Box = Cast<AAmmoBox>(OutHits[Hit].GetActor());
					BotCon->SetAmmoBox(Box);

					return EBTNodeResult::Succeeded;
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}
