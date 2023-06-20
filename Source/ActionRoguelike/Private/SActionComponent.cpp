#include "SActionComponent.h"
#include "SAction.h"
#include "ActionRoguelike/ActionRoguelike.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"

USActionComponent::USActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void USActionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USActionComponent, Actions);
}

bool USActionComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	for(USAction* Action : Actions) {
		if(Action)
			WroteSomething |= Channel->ReplicateSubobject(Action, *Bunch, *RepFlags);
	}
	return WroteSomething;
}

void USActionComponent::BeginPlay()
{
	Super::BeginPlay();

	if(GetOwner()->HasAuthority())
	{
		for (TSubclassOf<USAction> ActionClass : DefaultActions)
		{
			AddAction(GetOwner(), ActionClass);
		}
	}
}

void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, DebugMsg);
	for(USAction* Action : Actions)
	{
		FColor TextColor = Action->IsRunning() ? FColor::Blue : FColor::White;

		FString ActionMsg = FString::Printf(TEXT("[%s] Action %s : IsRunning: %s : Outer: %s"),
			*GetNameSafe(GetOwner()), *Action->ActionName.ToString(),
			Action->IsRunning() ? TEXT("true") : TEXT("false"),
			*GetNameSafe(Action->GetOuter()));

		LogOnScreen(this, ActionMsg, TextColor, 0.f);
	}
}

bool USActionComponent::AddAction(AActor* Instigator, TSubclassOf<USAction> ActionClass)
{
	if(!ensure(ActionClass))
		return false;

	
	/*for (const USAction* Action : Actions)
	{
		if(Action->IsA(ActionClass))
		{
			FString DebugMsg = FString::Printf(TEXT("Action '%s' already known."), *GetNameSafe(ActionClass));			
			GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, DebugMsg);
			return false;
		}
	}*/
	
	USAction* NewAction = NewObject<USAction>(GetOwner(), ActionClass);
	if(!ensure(NewAction))
		return false;

	NewAction->Initialize(this);
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
