#include "SActionEffect.h"

#include "BlueprintEditor.h"
#include "SActionComponent.h"

USActionEffect::USActionEffect()
{
	bAutoStart = true;
}

void USActionEffect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	if(Duration>0.0f)
	{
		FTimerDelegate DurationTimerDelegate;
		DurationTimerDelegate.BindUFunction(this, "StopAction", Instigator);
		GetWorld()->GetTimerManager().SetTimer(DurationHandle, DurationTimerDelegate, Duration, false);
	}

	if(Period>0.0f)
	{
		FTimerDelegate PeriodTimerDelegate;
		PeriodTimerDelegate.BindUFunction(this, "ExecutePeriodicEffect", Instigator);
		GetWorld()->GetTimerManager().SetTimer(PeriodHandle, PeriodTimerDelegate, Period, true);			
	}	
}

void USActionEffect::StopAction_Implementation(AActor* Instigator)
{
	if(GetWorld()->GetTimerManager().GetTimerRemaining(PeriodHandle) < KINDA_SMALL_NUMBER)
		ExecutePeriodicEffect(Instigator);
	
	Super::StopAction_Implementation(Instigator);
	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);
	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);

	if(USActionComponent* Comp = GetOwningComponent())
		Comp->RemoveAction(this);
}

void USActionEffect::ExecutePeriodicEffect_Implementation(AActor* Instigator)
{
}