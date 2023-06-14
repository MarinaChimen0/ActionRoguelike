#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SProjectileBaseActor.h"
#include "SMagicProjectile.generated.h"

class USoundCue;
class UParticleSystem;

/*
 * @brief	Magic projectile actor.
 */
UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public ASProjectileBaseActor
{
	GENERATED_BODY()

protected:

// Protected variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	float Damage = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	FGameplayTag ParryTag;
	
// Protected methods
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * @brief	Called when the destructor sphere is overlapped by another actor.
	 */
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
