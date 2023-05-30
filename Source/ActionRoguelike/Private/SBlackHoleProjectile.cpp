#include "SBlackHoleProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASBlackHoleProjectile::ASBlackHoleProjectile()
{
	SphereComp->SetCollisionProfileName("OverlapAll");
	
	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(SphereComp);
	ForceComp->Radius = 1000.0f;
	ForceComp->ForceStrength = -2000000.0f;
	ForceComp->bImpulseVelChange = true;
	ForceComp->RemoveObjectTypeToAffect(TEnumAsByte<EObjectTypeQuery>(ECC_Pawn));
}

// Called when the game starts or when spawned
void ASBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);//Destroy it after 5s matching the particle system duration
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OverlapBegin);
}

void ASBlackHoleProjectile::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!OtherComp->IsSimulatingPhysics())
		return;

	OtherActor->Destroy();
}

void ASBlackHoleProjectile::Destroyed()
{
	Super::Destroyed();
}

