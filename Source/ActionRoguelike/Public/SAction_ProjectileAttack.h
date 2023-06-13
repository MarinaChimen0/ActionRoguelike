#pragma once
#include "CoreMinimal.h"
#include "SAction.h"
#include "SAction_ProjectileAttack.generated.h"

class UAnimMontage;
class UParticleSystem;

/**
 * @brief	Projectile attack action class.
 */
UCLASS()
class ACTIONROGUELIKE_API USAction_ProjectileAttack : public USAction
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> ProjectileClass;
	
	UPROPERTY(VisibleAnywhere, Category="Effects")
	FName HandSocketName = "Muzzle_01";
	
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay = 0.2f;
	
	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnim;
	
	UPROPERTY(EditAnywhere, Category = "Attack")
	UParticleSystem* CastingEffect;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);

public:

	USAction_ProjectileAttack();
	
	virtual void StartAction_Implementation(AActor* Instigator) override;
};
