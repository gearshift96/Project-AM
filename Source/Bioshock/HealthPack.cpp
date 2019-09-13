// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"
#include "Components/BoxComponent.h"
#include "AICharacter.h"

void AHealthPack::OnComponentBeginOverlap(UPrimitiveComponent* OveralappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AAICharacter* Bot = Cast<AAICharacter>(OtherActor);
		if (Bot)
		{
			//A bot came and collected this health pack
			Bot->Heal(FMath::RandRange(100, 200));
			Destroy();
		}
	}
}

// Sets default values
AHealthPack::AHealthPack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthPackSM = CreateDefaultSubobject<UStaticMeshComponent>(FName("HealthPackSM"));

	if (HealthPackSM)
	{
		SetRootComponent(HealthPackSM);
	}

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));
	if (CollisionBox)
	{
		CollisionBox->AttachToComponent(HealthPackSM, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	}

}

// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AHealthPack::OnComponentBeginOverlap);
	}

}

// Called every frame
void AHealthPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


