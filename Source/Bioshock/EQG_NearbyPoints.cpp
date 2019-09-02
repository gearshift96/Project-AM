// Fill out your copyright notice in the Description page of Project Settings.

#include "EQG_NearbyPoints.h"

void UEQG_NearbyPoints::GenerateItems(FEnvQueryInstance & QueryInstance) const
{
	TArray<FNavLocation> LocationCandidates;

	AActor* AIPawn = Cast<AActor>((QueryInstance.Owner).Get());

	if (!AIPawn || AngleStep <= 0) return;

	FVector PawnLocation = AIPawn->GetActorLocation();
	FVector PawnForwardVector = AIPawn->GetActorForwardVector();

	for (float Angle = DegreesGap; Angle < 360 - DegreesGap; Angle += AngleStep)
	{
		FVector RightVector = PawnForwardVector.RotateAngleAxis(Angle, FVector::UpVector);

		for (float Distance = PointsDistance; Distance < MaxRange; Distance += PointsDistance)
		{
			FNavLocation NavLocation = FNavLocation(PawnLocation + RightVector * Distance);
			LocationCandidates.Add(NavLocation);
		}

	}

	//Project the generated points and store them as the result of this generator
	ProjectAndFilterNavPoints(LocationCandidates, QueryInstance);
	StoreNavPoints(LocationCandidates, QueryInstance);
}
