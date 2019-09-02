// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "BotController.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "NavArea_Crouch.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAICharacter::AAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}


