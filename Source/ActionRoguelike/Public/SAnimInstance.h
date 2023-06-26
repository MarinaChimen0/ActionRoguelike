#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SAnimInstance.generated.h"

class USActionComponent;
/**
 * @brief	Custom animation instance for the character.
 */
UCLASS()
class ACTIONROGUELIKE_API USAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	bool bIsStunned;

	UPROPERTY(BlueprintReadOnly, Category="Animation")
	USActionComponent* ActionComp;
	
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
