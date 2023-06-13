#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

/**
 * @brief	Custom player state.
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	// Public delegate
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, ASPlayerState*, PlayerState, int32, NewCreditsAmount, int32, Delta);
	UPROPERTY(BlueprintAssignable)
	FOnCreditsChanged OnCreditsChanged;
	
	// Public methods

	UFUNCTION(BlueprintCallable)
	void AddCredits(int32 Amount);

	UFUNCTION(BlueprintCallable)
	bool RemoveCredits(int32 Amount);

private:

	// Private variables

	int32 CreditsAmount = 0;
	
};
