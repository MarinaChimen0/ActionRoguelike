#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SAction.generated.h"

class USActionComponent;
class UWorld;

USTRUCT()
struct FActionRepData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	bool bIsRunning;

	UPROPERTY()
	AActor* Instigator;
	
};

/**
 * @brief	Action base class.
 */
UCLASS(Blueprintable)
class ACTIONROGUELIKE_API USAction : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FGameplayTagContainer GrantTags;

	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(ReplicatedUsing="OnRep_RepData")
	FActionRepData RepData;

	UPROPERTY(Replicated)
	float TimeStarted;
	
	UPROPERTY(Replicated)
	USActionComponent* ActionComp;

	UFUNCTION()
	void OnRep_RepData();
	
	UFUNCTION(BlueprintCallable, Category="Action")
	USActionComponent* GetOwningComponent() const;
	
public:

	UPROPERTY(EditDefaultsOnly, Category="Action")
	bool bAutoStart;
	
	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName ActionName;
	
	void Initialize(USActionComponent* NewActionComp);

	UFUNCTION(BlueprintCallable, Category="Action")
	bool IsRunning() const;
	
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Action")
	void StopAction(AActor* Instigator);

	virtual UWorld* GetWorld() const override;
	
	/** IsSupportedForNetworking means an object can be referenced over the network */
	virtual bool IsSupportedForNetworking() const override;
	
};
