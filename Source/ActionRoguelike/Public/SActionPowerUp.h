#pragma once

#include "CoreMinimal.h"
#include "SPowerUpBaseActor.h"
#include "SActionPowerUp.generated.h"

class USAction;
/**
 * @brief	Power up that grants an action.
 */
UCLASS()
class ACTIONROGUELIKE_API ASActionPowerUp : public ASPowerUpBaseActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USAction> ActionClass;
	
	virtual bool ApplyPowerUp(APawn* InstigatorPawn) override;
	
};
