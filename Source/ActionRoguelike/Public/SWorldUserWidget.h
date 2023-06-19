#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SWorldUserWidget.generated.h"

class USizeBox;

/**
 * @brief	World ser widget class.
 */
UCLASS()
class ACTIONROGUELIKE_API USWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category="UI", meta=(ExposeOnSpawn=true))
	AActor* AttachedActor;

	UPROPERTY(EditAnywhere, Category="UI")
	FVector WorldOffset;
	
protected:

	UPROPERTY(meta=(BindWidget))
	USizeBox* ParentSizeBox;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
