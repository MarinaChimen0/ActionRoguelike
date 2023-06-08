#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OverlapBegin);
}

void ASMagicProjectile::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!OtherActor && OtherActor != GetInstigator())
		return;

	if(USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass())))
	{
		AttributeComp->ApplyHealthChange(GetInstigator(), -Damage);
		UGameplayStatics::PlayWorldCameraShake(GetWorld(), ImpactCameraShake, GetActorLocation(), ImpactInnerRadius, ImpactOuterRadius);
		Explode();
	}
} 