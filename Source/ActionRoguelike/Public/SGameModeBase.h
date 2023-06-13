#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;
class ASPowerUpBaseActor;

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
	
	virtual void StartPlay() override;
	
	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	UFUNCTION(Exec)
	void KillAll();

protected:

	// Protected variables

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AActor> MinionClass;

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
	
	// Protected methods

	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION()
	void OnMinionSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void OnPowerUpSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	
	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);
	
};
