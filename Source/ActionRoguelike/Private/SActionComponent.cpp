#include "SActionComponent.h"
#include "SAction.h"
#include "ActionRoguelike/ActionRoguelike.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"

DECLARE_CYCLE_STAT(TEXT("StartAction"), STAT_StartAction, STATGROUP_STANFORD);

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

void USActionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	TArray<USAction*> ActionsCopy = Actions;
	for (USAction* Action : ActionsCopy)
	{
		if(Action && Action->IsRunning())
			Action->StopAction(GetOwner());
	}
	
	Super::EndPlay(EndPlayReason);
}

void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, DebugMsg);
	for(USAction* Action : Actions)
	{
		FColor TextColor = Action->IsRunning() ? FColor::Blue : FColor::White;

		FString ActionMsg = FString::Printf(TEXT("[%s] Action %s : IsRunning: %s"),
			*GetNameSafe(GetOwner()), *GetNameSafe(Action),
			Action->IsRunning() ? TEXT("true") : TEXT("false"));

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

	if(!GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Client attempting to AddAction. [Class: %s]"), *GetNameSafe(ActionClass));
		return false;
	}
	
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
	SCOPE_CYCLE_COUNTER(STAT_StartAction);
	
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
			{
				ServerStartAction(Instigator, ActionName);
			}

			TRACE_BOOKMARK(TEXT("StartAction::%s"), *GetNameSafe(Action));
			
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
				if(!GetOwner()->HasAuthority())
				{
					ServerStopAction(Instigator, ActionName);
				}
				
				Action->StopAction(Instigator);
				return true;
			}
		}
	}
	return false;
}


void USActionComponent::ServerStopAction_Implementation(AActor* Instigator, FName ActionName)
{
	StopAction(Instigator, ActionName);
}