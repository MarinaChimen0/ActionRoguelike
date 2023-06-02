// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpBaseActor.h"

#include "Components/SphereComponent.h"

// Sets default values
ASPowerUpBaseActor::ASPowerUpBaseActor()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionProfileName("Powerup");
	RootComponent = SphereComponent;

}

void ASPowerUpBaseActor::Interact_Implementation(APawn* InstigatorPawn)
{
	ApplyPowerUp(InstigatorPawn);
	Deactivate();
}

// Called when the game starts or when spawned
void ASPowerUpBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASPowerUpBaseActor::ApplyPowerUp(APawn* InstigatorPawn)
{
}

void ASPowerUpBaseActor::SetPowerupState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);
	RootComponent->SetVisibility(bNewIsActive, true);
}

void ASPowerUpBaseActor::Activate()
{
	SetPowerupState(true);
}

void ASPowerUpBaseActor::Deactivate()
{
	SetPowerupState(false);
	FTimerHandle ActivateTimer;
	GetWorldTimerManager().SetTimer(ActivateTimer, this, &ASPowerUpBaseActor::Activate, InactiveTime);
}

