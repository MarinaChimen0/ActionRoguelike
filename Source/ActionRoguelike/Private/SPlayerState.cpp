#include "SPlayerState.h"

void ASPlayerState::AddCredits(int32 Amount)
{
	if(!ensure(Amount>0))
		return;
	
	CreditsAmount+=Amount;
	OnCreditsChanged.Broadcast(this, CreditsAmount, Amount);
}

bool ASPlayerState::RemoveCredits(int32 Amount)
{
	if(!ensure(Amount>0))
		return false;
	
	if(Amount>CreditsAmount)
		return false;

	CreditsAmount-=Amount;
	OnCreditsChanged.Broadcast(this, CreditsAmount, Amount);
	return true;
}
