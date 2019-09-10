// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class BIOSHOCK_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Current Health of this bot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float Health;

	/* Max health of bots */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float MaxHealth;

public:	

	/* Returns true if the bot is currently alive */
	UFUNCTION(BlueprintCallable, Category = "Player")
	FORCEINLINE bool IsAlive() const { return Health > 0; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
