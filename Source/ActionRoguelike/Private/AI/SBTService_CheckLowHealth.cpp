#include "AI/SBTService_CheckLowHealth.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* MyPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if(ensure(MyPawn))
	{
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(MyPawn);
		if (ensure(AttributeComp))
		{
			UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
			BlackboardComponent->SetValueAsBool(LowHealthKey.SelectedKeyName, AttributeComp->GetHealth()/AttributeComp->GetHealthMax()<LowHealthPercent);
		}
	}
}
