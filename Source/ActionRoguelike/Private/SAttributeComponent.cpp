#include "SAttributeComponent.h"

#include "SGameModeBase.h"
#include "Net/UnrealNetwork.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);

USAttributeComponent::USAttributeComponent()
{
	Health = HealthMax;
	SetIsReplicatedByDefault(true);
}

void USAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USAttributeComponent, Health);
	DOREPLIFETIME(USAttributeComponent, HealthMax);

	//DOREPLIFETIME_CONDITION(USAttributeComponent, HealthMax, COND_InitialOnly);
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if(FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}
	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	if(USAttributeComponent* AttributeComponent = GetAttributes(Actor))
		return AttributeComponent->IsAlive();

	return false;
}

// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = HealthMax;
}

void USAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if(!GetOwner()->CanBeDamaged() && Delta<0.0f)
		return false;

	if(Delta<0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
		Delta *= DamageMultiplier;
	}
	
	float OldHealth = Health;
	Health = FMath::Clamp(Health+Delta, 0.0f, HealthMax);
	float ActualDelta = Health - OldHealth;

	//OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);
	if(ActualDelta!=0)
		MulticastHealthChanged(InstigatorActor, Health, ActualDelta);
	
	if(ActualDelta<0.0f && Health==0.0f)
	{
		if(ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>())
			GM->OnActorKilled(GetOwner(), InstigatorActor);
	}
		
	return ActualDelta != 0;
}

bool USAttributeComponent::IsAlive() const
{
	return  Health > 0.0f;
}

bool USAttributeComponent::IsHealthMax() const
{
	return Health == HealthMax;
}

float USAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

float USAttributeComponent::GetHealth() const
{
	return Health;
}

bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetHealthMax());
}

bool USAttributeComponent::ApplyRageChange(AActor* InstigatorActor, float Delta)
{
	if(Delta < 0 && FMath::Abs(Delta)>Rage)
		return false;
	
	float OldRage = Rage;
	Rage = FMath::Clamp(Rage+Delta, 0.0f, RageMax);
	float ActualDelta = Rage - OldRage;

	OnRageChanged.Broadcast(InstigatorActor, this, Rage, ActualDelta);
	
	return true;
}

float USAttributeComponent::GetRage() const
{
	return Rage;
}
