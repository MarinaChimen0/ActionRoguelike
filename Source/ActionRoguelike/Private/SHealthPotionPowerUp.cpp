#include "SHealthPotionPowerUp.h"
#include "SAttributeComponent.h"
#include "SPlayerState.h"

#define LOCTEXT_NAMESPACE "InteractableActors"

ASHealthPotionPowerUp::ASHealthPotionPowerUp()
{
}

FText ASHealthPotionPowerUp::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	if(AttributeComp && AttributeComp->IsHealthMax())
	{
		return LOCTEXT("HealthPotion_FullHealthWarning", "Already at full health.");
	}
	return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Cost {0} Credits. Restores health to maximum."), CreditCost);
}

bool ASHealthPotionPowerUp::ApplyPowerUp(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
		return false;
	
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	if(!ensure(AttributeComp) || AttributeComp->IsHealthMax())
		return false;

	if(ASPlayerState* PlayerState = InstigatorPawn->GetPlayerState<ASPlayerState>())
		if(!PlayerState->RemoveCredits(CreditCost))
			return false;

	return AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax());
}

#undef LOCTEXT_NAMESPACE
