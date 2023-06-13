#include "SAction.h"

void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));
}

UWorld* USAction::GetWorld() const
{
	if(UActorComponent* Comp = Cast<UActorComponent>(GetOuter()))
	{
		return Comp->GetWorld();
	}
	return nullptr;
}
