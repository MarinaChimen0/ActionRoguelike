#include "SHealthPotionPowerUp.h"

#include "SAttributeComponent.h"

ASHealthPotionPowerUp::ASHealthPotionPowerUp()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetupAttachment(RootComponent);
}

void ASHealthPotionPowerUp::ApplyPowerUp(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
		return;

	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	if(ensure(AttributeComp) && !AttributeComp->IsHealthMax())
		AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax());
}


