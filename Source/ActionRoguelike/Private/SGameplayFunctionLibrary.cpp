
#include "SGameplayFunctionLibrary.h"

#include "SAttributeComponent.h"

bool USGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	if(USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttributes(TargetActor))
		return AttributeComponent->ApplyHealthChange(DamageCauser, -DamageAmount);
	return false;
}

bool USGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount,
	const FHitResult& HitResult)
{
	if(ApplyDamage(DamageCauser, TargetActor,  DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		if(HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			HitComp->AddImpulseAtLocation(-HitResult.ImpactNormal*300000., HitResult.ImpactPoint, HitResult.BoneName);
		}
		return true;
	}
	return false;
}
