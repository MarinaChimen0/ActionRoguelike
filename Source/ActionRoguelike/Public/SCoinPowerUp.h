#pragma once
#include "CoreMinimal.h"
#include "SPowerUpBaseActor.h"
#include "SCoinPowerUp.generated.h"

/**
 * @brief	Coin to get credits power up.
 */
UCLASS()
class ACTIONROGUELIKE_API ASCoinPowerUp : public ASPowerUpBaseActor
{
	GENERATED_BODY()

protected:

	// Protected variables

	UPROPERTY(EditAnywhere, Category = "Credits")
	int32 CreditAmount = 5;
	
	virtual bool ApplyPowerUp(APawn* InstigatorPawn) override;
	
};
