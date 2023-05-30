#pragma once

#include "CoreMinimal.h"
#include "SProjectileBaseActor.h"
#include "SBlackHoleProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;


/*
 * @brief	Black hole projectile actor.
 */
UCLASS()
class ACTIONROGUELIKE_API ASBlackHoleProjectile : public ASProjectileBaseActor
{
	GENERATED_BODY()
	
public: // Public variables
	
	// Radial force component to attract objects
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ForceComp;

	// Lifespan of the projectile
	UPROPERTY(VisibleAnywhere)
	float LifeSpan = 5;

public:	//Public methods

	// Sets default values for this actor's properties
	ASBlackHoleProjectile();

protected: // Protected methods
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private: // Private methods

	/**
	 * @brief	Called when the destructor sphere is overlapped by another actor.
	 */
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	// Called when 
	virtual void Destroyed() override;
	
};
