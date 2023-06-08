#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

/**
 * @brief	AAttribute component class.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	//Public delegates

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
//Public methods

	UFUNCTION(BlueprintCallable, Category="Attributes")
	static USAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category="Attributes", meta = (DisplayName = "IsAlive"))
	static bool IsActorAlive(AActor* Actor);
	
	// Sets default values for this component's properties
	USAttributeComponent();

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	bool IsHealthMax() const;

	UFUNCTION(BlueprintCallable)
	float GetHealthMax() const;

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	bool Kill(AActor* InstigatorActor);
	
protected:

//Protected variables  	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float HealthMax = 100;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float Health;

//Protected methods
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
