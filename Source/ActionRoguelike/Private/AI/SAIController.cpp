#include "AI/SAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();


	if(ensureMsgf(BehaviorTree, TEXT("Behaviour Tree is nullptr! Please assign BehaviourTree in your AI Controller.")))
	{
		RunBehaviorTree(BehaviorTree);
	}

	/*if(APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0))
	{
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	}*/
		
}
