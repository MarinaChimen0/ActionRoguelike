#include "SCoinPowerUp.h"

#include "SPlayerState.h"

bool ASCoinPowerUp::ApplyPowerUp(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
		return false;

	if(ASPlayerState* PlayerState = InstigatorPawn->GetPlayerState<ASPlayerState>())
	{
		PlayerState->AddCredits(CreditAmount);
		return true;
	}

	return false;
}
