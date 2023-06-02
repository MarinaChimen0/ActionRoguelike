#include "AI/SBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if(ensure(BlackboardComponent))
	{
		if(const AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor")))
		{
			const AAIController* MyController = OwnerComp.GetAIOwner();
			if(ensure(MyController))
			{
				const APawn* AIPawn = MyController->GetPawn();
				if(ensure(AIPawn))
				{
					const float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());
					const bool bWithinRange = DistanceTo < 2000.f;
					bool bHasLOS = false;
					if(bWithinRange)
						bHasLOS = MyController->LineOfSightTo(TargetActor);
					BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange && bHasLOS);
				}
			}
		}
	}
}
