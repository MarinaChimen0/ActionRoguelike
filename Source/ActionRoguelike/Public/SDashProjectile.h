#pragma once

#include "CoreMinimal.h"
#include "SProjectileBaseActor.h"
#include "SDashProjectile.generated.h"

/**
 *	@brief Teleport projectile.
 */
UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASProjectileBaseActor
{
	GENERATED_BODY()

public: // Public variables
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DetonateDelay = 0.2f;

public:	// Public methods

	/**
	 *	@brief Constructor.
	*/
	ASDashProjectile();

protected: // Protected methods

	// Base class using BlueprintNativeEvent, we must override the _Implementation not the Explode()
	virtual void Explode_Implementation() override;

	void TeleportInstigator();

	virtual void BeginPlay() override;
	
private: // Private variables

	// Handle to cancel timer if we already hit something
	FTimerHandle TimerHandle_DelayedDetonate;
	
};
