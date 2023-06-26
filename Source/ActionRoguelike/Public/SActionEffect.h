#pragma once
#include "CoreMinimal.h"
#include "SAction.h"
#include "SActionEffect.generated.h"

/**
 * @brief	Effect action.
 */
UCLASS()
class ACTIONROGUELIKE_API USActionEffect : public USAction
{
	GENERATED_BODY()

public:

	USActionEffect();
	
	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;
	
	UFUNCTION(BlueprintCallable, Category="Action")
	float GetTimeRemaining() const;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effect")
	float Duration;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effect")
	float Period;

	FTimerHandle PeriodHandle;
	FTimerHandle DurationHandle;

	UFUNCTION(BlueprintNativeEvent, Category="Effect")
	void ExecutePeriodicEffect(AActor* Instigator);
	
};
