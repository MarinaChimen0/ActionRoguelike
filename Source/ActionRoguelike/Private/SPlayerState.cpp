#include "SPlayerState.h"

#include "SSaveGame.h"
#include "Net/UnrealNetwork.h"

void ASPlayerState::AddCredits(int32 Amount)
{
	if(!ensure(Amount>0))
		return;
	
	CreditsAmount+=Amount;
	MulticastCreditsChanged(CreditsAmount, Amount);
}

bool ASPlayerState::RemoveCredits(int32 Amount)
{
	if(!ensure(Amount>0))
		return false;
	
	if(Amount>CreditsAmount)
		return false;

	CreditsAmount-=Amount;
	//OnCreditsChanged.Broadcast(this, CreditsAmount, Amount);
	MulticastCreditsChanged(CreditsAmount, Amount);
	return true;
}

int32 ASPlayerState::GetCredits() const
{
	return CreditsAmount;
}

void ASPlayerState::SavePlayerState_Implementation(USSaveGame* SaveObject)
{
	if(SaveObject)
	{
		SaveObject->Credits = CreditsAmount;
	}
}

void ASPlayerState::LoadPlayerState_Implementation(USSaveGame* SaveObject)
{
	if(SaveObject){
		AddCredits(SaveObject->Credits);
	}
}

void ASPlayerState::MulticastCreditsChanged_Implementation(int32 NewCreditsAmount, int32 Amount)
{
	OnCreditsChanged.Broadcast(this, NewCreditsAmount, Amount);
}

void ASPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPlayerState, CreditsAmount);
}
