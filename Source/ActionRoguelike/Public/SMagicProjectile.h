#pragma once

#include "CoreMinimal.h"
#include "SProjectileBaseActor.h"
#include "SMagicProjectile.generated.h"

class UParticleSystem;

/*
 * @brief	Magic projectile actor.
 */
UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public ASProjectileBaseActor
{
	GENERATED_BODY()

protected: // Protected methods
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
