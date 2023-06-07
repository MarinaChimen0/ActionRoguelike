#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTask_Heal.generated.h"

/**
 * @brief	BT Task to heal back to max.
 */
UCLASS()
class ACTIONROGUELIKE_API USBTTask_Heal : public UBTTaskNode
{
	GENERATED_BODY()
	
	/** starts this task, should return Succeeded, Failed or InProgress
	 *  (use FinishLatentTask() when returning InProgress)
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
