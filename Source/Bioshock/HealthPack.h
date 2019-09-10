// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPack.generated.h"

UCLASS()
class BIOSHOCK_API AHealthPack : public AActor
{
	GENERATED_BODY()
	
private:

	/* Called when something overlaps with the CollisionBox */
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OveralappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Sets default values for this actor's properties
	AHealthPack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* The amount of health that this pack can contain */
	UPROPERTY(EditAnywhere, config, meta = (ClampMin = "10.0", ClampMax = "75.0"))
	float HealthAmount = 25.0;


	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* HealthPackSM;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
