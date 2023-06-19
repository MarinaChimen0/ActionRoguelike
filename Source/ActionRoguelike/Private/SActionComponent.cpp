#include "SActionComponent.h"
#include "SAction.h"

USActionComponent::USActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<USAction> ActionClass : DefaultActions)
	{
		AddAction(GetOwner(), ActionClass);
	}
}

void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, DebugMsg);
}

bool USActionComponent::AddAction(AActor* Instigator, TSubclassOf<USAction> ActionClass)
{
	if(!ensure(ActionClass))
		return false;

	
	for (const USAction* Action : Actions)
	{
		if(Action->IsA(ActionClass))
		{
			FString DebugMsg = FString::Printf(TEXT("Action '%s' already known."), *GetNameSafe(ActionClass));			
			GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, DebugMsg);
			return false;
		}
	}
	
	USAction* NewAction = NewObject<USAction>(this, ActionClass);
	if(!ensure(NewAction))
		return false;
    			
	Actions.Add(NewAction);
	if(NewAction->bAutoStart && ensure(NewAction->CanStart(Instigator)))
	{
		NewAction->StartAction(Instigator);
	}	
	return true;
}

void USActionComponent::RemoveAction(USAction* Action)
{
	if(!ensure(Action && !Action->IsRunning()))
		return;
	
	Actions.Remove(Action);
}

bool USActionComponent::StartAction(AActor* Instigator, FName ActionName)
{
	for(USAction* Action: Actions)
	{
		if(Action && Action->ActionName == ActionName)
		{
			if(!Action->CanStart(Instigator))
			{
				FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				continue;
			}
			
			if(!GetOwner()->HasAuthority())
				ServerStartAction(Instigator, ActionName);
					
			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

void USActionComponent::ServerStartAction_Implementation(AActor* Instigator, FName ActionName)
{
	StartAction(Instigator, ActionName);
}

bool USActionComponent::StopAction(AActor* Instigator, FName ActionName)
{
	for(USAction* Action: Actions)
	{
		if(Action && Action->ActionName == ActionName)
		{
			if(Action->IsRunning())
			{
				Action->StopAction(Instigator);
				return true;
			}
		}
	}
	return false;
}

