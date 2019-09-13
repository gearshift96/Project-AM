// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckForHealth.h"
#include "AICharacter.h"
#include "BotController.h"

void UBTService_CheckForHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	ABotController* BotCon = Cast<ABotController>(OwnerComp.GetAIOwner());
	if (BotCon)
	{
		AAICharacter* Bot = Cast<AAICharacter>(BotCon->GetCharacter());

		if (Bot)
		{
			//GLog->Log("setting low on ammo");
			if (Bot->LowOnHealth())
			{
				GLog->Log("I need health: " + Bot->GetName());
				GLog->Log("Current health: " + FString::FromInt(Bot->GetCurrentHealth()));
			}
			BotCon->SetCollectHealthStatus(Bot->LowOnHealth());
			/*if (BotCon)
			{
				GLog->Log("setting low on health");
				BotCon->SetCollectHealthStatus(Bot->LowOnHealth());
			}*/
		}
	}
}
