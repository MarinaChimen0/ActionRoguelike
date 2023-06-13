#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SAction.generated.h"

class UWorld;

/**
 * @brief	Action base class.
 */
UCLASS(Blueprintable)
class ACTIONROGUELIKE_API USAction : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName ActionName;

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StopAction(AActor* Instigator);

	virtual UWorld* GetWorld() const override;
};
