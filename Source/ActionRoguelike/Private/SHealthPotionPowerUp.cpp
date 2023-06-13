#include "SHealthPotionPowerUp.h"
#include "SAttributeComponent.h"
#include "SPlayerState.h"

ASHealthPotionPowerUp::ASHealthPotionPowerUp()
{
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


