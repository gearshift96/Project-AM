// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "BotController.h"
#include "Particles/ParticleSystemComponent.h"
#include "Projectile.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "NavArea_Crouch.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ExplosiveHazard.h"

bool AAICharacter::CanSeeSelectedTarget() const
{
	//Perform a line trace to check if the target is currently LOSing the bot
	//We don't want to fire at wall and get blamed for wallhack :(
	ABotController* BotController = Cast<ABotController>(GetController());
	if (BotController && BotController->GetSelectedTarget())
	{
		FVector TargetLocation = BotController->GetSelectedTargetLocation();

		FCollisionObjectQueryParams CollisionObjectQueryParams = FCollisionObjectQueryParams(ECC_WorldDynamic);
		CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

		FHitResult HitResult;
		FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(FName("BotLineTrace"));
		CollisionQueryParams.AddIgnoredActor(this);

		if (GetWorld()->LineTraceSingleByObjectType(HitResult, GetActorLocation(), TargetLocation, CollisionObjectQueryParams, CollisionQueryParams))
		{
			AAICharacter* Character = Cast<AAICharacter>(HitResult.GetActor());
			if (Character)
			{
				return true;
			}
		}
		else
		{
			AExplosiveHazard* Hazard = Cast<AExplosiveHazard>(HitResult.GetActor());
			if (Hazard)
			{
				return true;
			}
		}
	}
	return false;
}

bool AAICharacter::CanFireWeapon() const
{
	return (Health > 0) && (CurrentAmmo > 0) && (LastFireWeaponTime >= FireRate);
}

// Sets default values
AAICharacter::AAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Init properties
	FHealth = 200.f;
	Health = 200.f;
	CurrentAmmo = 30;
	MeshCrouchAdjustLocation = FVector(0, 0, -70);
	RetreatHealthPercentage = 0.2f;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

float AAICharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	Health -= Damage;
	//TODO:Play hit montage

	//Should we retreat?
	if (LowOnHealth())
	{
		ABotController* BotController = Cast<ABotController>(GetController());
		if (BotController)
		{
			BotController->InitiateRetreat();
		}
	}

	//If true the bot is dead so enable ragdoll physics and unposses to stop all AI logic
	if (!IsAlive())
	{
		//If the bot was crouching while he died we need to uncrouch first otherwise we're going to see
		//"funny" ragdoll effects
		if (GetCharacterMovement() && GetCharacterMovement()->IsCrouching())
		{
			GetCharacterMovement()->UnCrouch();
		}

		//Enable ragdoll physics
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName(FName("Ragdoll"));
		GetMesh()->SetCollisionResponseToAllChannels(ECR_Block);

		//We want the other pawns to be able to walk on us (since we're currently dead :( )
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

		if (GetController())
		{
			GetController()->UnPossess();
			//Manually update the bot counter
		}

		//Destroy the in-game actor after a few seconds
		FTimerHandle DestroyBotTimer;
		FTimerDelegate DestroyActorDelegate;
		DestroyActorDelegate.BindLambda([&]()
		{
			Destroy();
		});
		GetWorld()->GetTimerManager().SetTimer(DestroyBotTimer, DestroyActorDelegate, DestroyActorDelay, false);

		//GLog->Log("bot is dead activating ragdoll");
	}

	return Damage;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = FHealth;
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCharacterMovement())
	{
		//Adjust the mesh height in order to avoid having half of the mesh under the ground.
		if (GetCharacterMovement()->IsCrouching())
		{
			GetMesh()->SetRelativeLocation(FVector(0, 0, -70.f), true, nullptr, ETeleportType::TeleportPhysics);
		}
	}

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Health = FHealth;
}



