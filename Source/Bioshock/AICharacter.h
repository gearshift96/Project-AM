// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class BIOSHOCK_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

private:
	/*
	 * Identifies is the bot can actually see the target or if the target is currently LOSing this instance
	 * @return true - if we can see the target, false otherwise
	 */


	/* Time since this character fired */
	float LastFireWeaponTime;

	/* True if the character can fire the weapon again */

public:
	// Sets default values for this character's properties
	AAICharacter();

	/*
	 * Base Take Damage event that exists in Actor.h
	 * @see https://www.unrealengine.com/blog/damage-in-ue4
	 * @param DamageAmount		How much damage to apply
	 * @param DamageEvent		Data package that fully describes the damage received.
	 * @param EventInstigator	The Controller responsible for the damage.
	 * @param DamageCauser		The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
	 * @return					The amount of damage actually applied.
	 */
	//virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/* Adds the given amount of ammo to this bot */
	UFUNCTION(BlueprintCallable, Category = "AICharacter")
	 void AddAmmo(int32 Ammo) { CurrentAmmo += Ammo; }

	/* Get the current ammo of this bot */
	FORCEINLINE int32 GetCurrentAmmo() const { return CurrentAmmo; }

	/* Recovers the given amount of health to this bot */
	UFUNCTION(BlueprintCallable, Category = "AICharacter")
	 void Heal(float HealAmount) { Health += HealAmount; }

	/* Get the current health of this bot */
	FORCEINLINE float GetCurrentHealth() const { return Health; }


	UFUNCTION(BlueprintCallable, Category = "AICharacter")
	FORCEINLINE bool LowOnAmmo() const { return CurrentAmmo < 10; }

	UFUNCTION(BlueprintCallable, Category = "AICharacter")
	FORCEINLINE bool LowOnHealth() const { return Health <= FHealth * RetreatHealthPercentage;  }

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Current Health of this bot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AICharacter")
	float Health;

	/* Max health of bots */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AICharacter")
	float FHealth;

	/* Current Ammo of this bot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AICharacter")
	int32 CurrentAmmo;

	/* Sub class of the projectile actor class.
	 * Create a Blueprint based on this class and assign it here
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileBP;

	/* By default while crouching the bot's mesh is falling below the ground so adjust its location to avoid this effect */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MeshCrouchAdjustLocation = FVector(0, 0, -70);

	/* If the bot is dead destroy it after X seconds */
	UPROPERTY(EditAnywhere, Category = "AICharacter")
	float DestroyActorDelay;

	/* 
	 * The health value that will trigger the retreat behavior.
	 * A value of 0.2 means that the bot will treat when its health is <= FHealth * RetreatHealthPercentage
	 */
	UPROPERTY(EditAnywhere,config,meta=(ClampMin="0.0", ClampMax="1.0"))
	float RetreatHealthPercentage;

	/* 
	 * Delay between successful FireWeapon() calls to avoid firing multiple times in the same tick
	 * Treat this as the weapon's "FireRate".
	 */
	UPROPERTY(EditDefaultsOnly, Category = "AICharacter")
	float FireRate;

public:	

	/* Returns true if the bot is currently alive */
	UFUNCTION(BlueprintCallable, Category = "AICharacter")
	FORCEINLINE bool IsAlive() const { return Health > 0; }

	/* Attempts to fire 
	 * There are several rules that need to apply before we actually fire, such as:
	 * 1) A valid target must exist who is not LOSing this bot.
	 * 2) We need to have ammo before firing
	 * 3) The bot must be able to see the target who wishes to fire at
	 */

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Since this is not a playable character this should be erased on next iteration */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Construction script in the C++ side */
	virtual void OnConstruction(const FTransform& Transform) override;
};
