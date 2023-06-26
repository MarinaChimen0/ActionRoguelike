#include "SAction.h"

#include "SActionComponent.h"
#include "ActionRoguelike/ActionRoguelike.h"
#include "Net/UnrealNetwork.h"

void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(TEXT("Started: %s"), *ActionName.ToString()), FColor::Green);
	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantTags);
	RepData.bIsRunning = true;
	RepData.Instigator = Instigator;

	if(GetOwningComponent()->GetOwnerRole() == ROLE_Authority)
	{
		TimeStarted = GetWorld()->TimeSeconds;
	}
	GetOwningComponent()->OnActionStarted.Broadcast(GetOwningComponent(), this);
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(TEXT("Stopped: %s"), *ActionName.ToString()), FColor::White);
	//ensureAlways(bIsRunning);
	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantTags);
	RepData.bIsRunning = false;

	GetOwningComponent()->OnActionStopped.Broadcast(GetOwningComponent(), this);
}

void USAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USAction, RepData);
	DOREPLIFETIME(USAction, ActionComp);
	DOREPLIFETIME(USAction, TimeStarted);
}

void USAction::OnRep_RepData()
{
	if(RepData.bIsRunning)
	{
		StartAction(RepData.Instigator);
	} else
	{
		StopAction(RepData.Instigator);
	}
}

USActionComponent* USAction::GetOwningComponent() const
{
	//AActor* Actor = Cast<AActor>(GetOuter());
	//return Actor->GetComponentByClass(USActionComponent::StaticClass());
	
	//return Cast<USActionComponent>(GetOuter());

	return ActionComp;
}

void USAction::Initialize(USActionComponent* NewActionComp)
{
	ActionComp = NewActionComp;
}

bool USAction::IsRunning() const
{
	return RepData.bIsRunning;
}

bool USAction::CanStart_Implementation(AActor* Instigator)
{
	if(IsRunning())
		return false;
	
	USActionComponent* Comp = GetOwningComponent();
	return !Comp->ActiveGameplayTags.HasAny(BlockedTags);
}

UWorld* USAction::GetWorld() const
{
	if(AActor* Actor = Cast<AActor>(GetOuter()))
	{
		return Actor->GetWorld();
	}
	return nullptr;
}

bool USAction::IsSupportedForNetworking() const
{
	return true;
}
