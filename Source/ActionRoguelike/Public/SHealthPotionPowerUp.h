#pragma once

#include "CoreMinimal.h"
#include "SPowerUpBaseActor.h"
#include "SHealthPotionPowerUp.generated.h"

/**
 * @brief	Interactable health potion that heals the player.
 */
UCLASS()
class ACTIONROGUELIKE_API ASHealthPotionPowerUp : public ASPowerUpBaseActor
{
	GENERATED_BODY()

public:

	// Public methods

	ASHealthPotionPowerUp();
	
	virtual FText GetInteractText_Implementation(APawn* InstigatorPawn) override;
	
protected:

	// Protected variables

	UPROPERTY(EditAnywhere, Category = "Credits")
	int32 CreditCost = 2;
	
	virtual bool ApplyPowerUp(APawn* InstigatorPawn) override;
	
};
