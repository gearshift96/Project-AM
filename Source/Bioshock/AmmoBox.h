// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

UCLASS()
class BIOSHOCK_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
private:

	
	/* Called when something overlaps with the CollisionBox */
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OveralappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Sets default values for this actor's properties
	AAmmoBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* The minimum amount of ammo that this box can contain */
	UPROPERTY(EditAnywhere, meta = (ClampMin = '1'))
	int32 MinAmmo = 1;

	/* The maximum amount of ammo that this box can contain */
	UPROPERTY(EditAnywhere, meta = (ClampMin = '5'))
	int32 MaxAmmo = 5;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* AmmoBoxSM;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
