#include "SPowerUpBaseActor.h"
#include "Components/SphereComponent.h"

// Sets default values
ASPowerUpBaseActor::ASPowerUpBaseActor()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionProfileName("Powerup");
	RootComponent = SphereComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetupAttachment(RootComponent);
}

void ASPowerUpBaseActor::Interact_Implementation(APawn* InstigatorPawn)
{
	if(ApplyPowerUp(InstigatorPawn))
		Deactivate();
}

// Called when the game starts or when spawned
void ASPowerUpBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ASPowerUpBaseActor::ApplyPowerUp(APawn* InstigatorPawn)
{
	return false;
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

