#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPowerUpBaseActor.generated.h"

class USphereComponent;

/**
 * @brief	Interactable power up base class.
 */
UCLASS(Abstract)
class ACTIONROGUELIKE_API ASPowerUpBaseActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:

// Public methods
	
	// Sets default values for this actor's properties
	ASPowerUpBaseActor();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	virtual FText GetInteractText_Implementation(APawn* InstigatorPawn) override;

protected:

// Protected variables

	UPROPERTY(ReplicatedUsing="OnRep_IsActive")
	bool bIsActive = true;
	
	UPROPERTY(EditAnywhere, Category = "Powerup")
	float InactiveTime = 10;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	
// Protected methods
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool ApplyPowerUp(APawn* InstigatorPawn);

	UFUNCTION()
	void OnRep_IsActive();
	
private:

// Private methods

	void SetPowerupState(bool bNewIsActive);
	void Activate();
	void Deactivate();
	
};
