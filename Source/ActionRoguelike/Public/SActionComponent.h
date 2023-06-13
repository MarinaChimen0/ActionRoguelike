#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SActionComponent.generated.h"

class USAction;
/**
 * @brief	Action component.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	USActionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Actions")
	void AddAction(TSubclassOf<USAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StartAction(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StopAction(AActor* Instigator, FName ActionName);

protected:

	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<USAction>> DefaultActions;
	
	UPROPERTY()
	TArray<USAction*> Actions;

	virtual void BeginPlay() override;
	
};
