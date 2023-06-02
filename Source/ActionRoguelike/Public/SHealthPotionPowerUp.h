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
	
protected:

	// Protected variables
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	
	//UPROPERTY(EditAnywhere, Category = "Health")
	//float HealthAmount;
	
	// Protected methods

	virtual void ApplyPowerUp(APawn* InstigatorPawn) override;
	
};
