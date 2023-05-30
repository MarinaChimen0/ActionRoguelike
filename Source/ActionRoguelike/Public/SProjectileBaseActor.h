#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBaseActor.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

/*
 * @brief	Projectile base actor.
 */
UCLASS(Abstract)
class ACTIONROGUELIKE_API ASProjectileBaseActor : public AActor
{
	GENERATED_BODY()

public: // Public variables

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystem* HitParticleSystem = nullptr;
	
	// Sphere component 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	// Movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComp;

	// Effect component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* EffectComp;
	
public:	// Public methods
	
	// Sets default values for this actor's properties
	ASProjectileBaseActor();

protected: // Protected methods
	
	virtual void PostInitializeComponents() override;

	// On sphere component hit
	UFUNCTION()
	virtual void OnSphereCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Explosion function
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();
	
};
