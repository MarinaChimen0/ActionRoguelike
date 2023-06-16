#include "SActionPowerUp.h"

#include "SAction.h"
#include "SActionComponent.h"

bool ASActionPowerUp::ApplyPowerUp(APawn* InstigatorPawn)
{
	if(!ensure(InstigatorPawn && ActionClass))
		return false;
	
	if(USActionComponent* ActionComponent = Cast<USActionComponent>(InstigatorPawn->GetComponentByClass(USActionComponent::StaticClass())))
		return ActionComponent->AddAction(InstigatorPawn, ActionClass);                                                                                                     

	return false;
}
