#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

/**
 * @brief	Custom player controller.
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	
// Protected delegates
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnChanged, APawn*, NewPawn);
	UPROPERTY(BlueprintAssignable)
	FOnPawnChanged OnPawnChanged;

	// Listen for incoming player state (for clients this may be nullptr when initially joining a game, 
	// afterwards player state will not change again as PlayerControllers maintain the same player state throughout the level)
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChanged, APlayerState*, NewPlayerState);
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStateChanged OnPlayerStateReceived;

// Protected variables

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> PauseMenuClass;
	
	UPROPERTY()
	UUserWidget* PauseMenuInstance;

// Protected methods

	UFUNCTION(BlueprintCallable)
	void TogglePauseMenu();

	virtual void SetupInputComponent() override;

	virtual void SetPawn(APawn* InPawn) override;

	/* Called when player controller is ready to begin playing, good moment to initialize things like UI which might be too early in BeginPlay 
		(esp. in multiplayer clients where not all data such as PlayerState may have been received yet) */
	virtual void BeginPlayingState() override;

	UFUNCTION(BlueprintImplementableEvent)
	void BlueprintBeginPlayingState();

	virtual void OnRep_PlayerState() override;
	
};
