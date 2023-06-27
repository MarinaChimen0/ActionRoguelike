#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class USMonsterData;
class UDataTable;
class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;
class ASPowerUpBaseActor;
class USSaveGame;

USTRUCT(BlueprintType)
struct FMonsterInfoRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId MonsterId;
	//TSubclassOf<AActor> MonsterClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Weight = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnCost = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float KillReward = 20.0f;
	
};

/**
 * @brief	Custom game mode class.
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	// Public methods

	ASGameModeBase();

	/**
	 * Initialize the game.
	 * The GameMode's InitGame() event is called before any other functions (including PreInitializeComponents() )
	 * and is used by the GameMode to initialize parameters and spawn its helper classes.
	 * @warning: this is called before actors' PreInitializeComponents.
	 */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/** Signals that a player is ready to enter the game, which may start it up */
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	
	virtual void StartPlay() override;
	
	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	UFUNCTION(Exec)
	void KillAll();

	UFUNCTION(BlueprintCallable, Category="SaveGame")
	void WriteSaveGame();

	void LoadSaveGame();

protected:

	// Protected variables

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UDataTable* MonsterTable;

	// UPROPERTY(EditDefaultsOnly, Category="AI")
	// TSubclassOf<AActor> MinionClass;
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UCurveFloat* DifficultyCurve;
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	float SpawnTimerInterval = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category="PowerUps")
	UEnvQuery* SpawnPowerUpsQuery;

	UPROPERTY(EditDefaultsOnly, Category="PowerUps")
	TMap<TSubclassOf<ASPowerUpBaseActor>, int32> PowerUpClassesAndAmountsMap;

	UPROPERTY(EditDefaultsOnly, Category="PowerUps")
	float DistanceBetweenPowerUps = 2000.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Credits")
	int32 CreditsPerKill = 3;
	
	FTimerHandle TimerHandle_SpawnBots;

	FTimerHandle TimerHandle_SpawnPowerUps;

	FString SlotName;
	
	UPROPERTY()
	USSaveGame* CurrentSaveGame;
	
	// Protected methods

	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION()
	void OnMinionSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	void OnMonsterLoaded(FPrimaryAssetId LoadedId, FVector SpawnLocation);
	
	UFUNCTION()
	void OnPowerUpSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	
	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);
	
};
