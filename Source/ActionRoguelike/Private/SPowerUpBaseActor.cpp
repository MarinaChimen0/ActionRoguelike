#include "SPowerUpBaseActor.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASPowerUpBaseActor::ASPowerUpBaseActor()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionProfileName("Powerup");
	RootComponent = SphereComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetupAttachment(RootComponent);

	SetReplicates(true);
}

void ASPowerUpBaseActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPowerUpBaseActor, bIsActive);
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

void ASPowerUpBaseActor::OnRep_IsActive()
{
	SetPowerupState(bIsActive);
}

void ASPowerUpBaseActor::SetPowerupState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);
	RootComponent->SetVisibility(bNewIsActive, true);
}

void ASPowerUpBaseActor::Activate()
{
	bIsActive = true;
	SetPowerupState(bIsActive);
}

void ASPowerUpBaseActor::Deactivate()
{
	bIsActive = false;
	SetPowerupState(bIsActive);
	FTimerHandle ActivateTimer;
	GetWorldTimerManager().SetTimer(ActivateTimer, this, &ASPowerUpBaseActor::Activate, InactiveTime);
}

