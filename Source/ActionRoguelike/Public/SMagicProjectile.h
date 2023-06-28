#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SProjectileBaseActor.h"
#include "SMagicProjectile.generated.h"

class USActionEffect;
class USoundCue;
class UParticleSystem;

/*
 * @brief	Magic projectile actor.
 */
UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public ASProjectileBaseActor
{
	GENERATED_BODY()

public:

	ASMagicProjectile();

protected:

// Protected variables

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float Damage = 50;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FGameplayTag ParryTag;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TSubclassOf<USActionEffect> BurningActionClass;
	
// Protected methods
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * @brief	Called when the destructor sphere is overlapped by another actor.
	 */
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
