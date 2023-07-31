#include "AI/SAICharacter.h"

#include "BrainComponent.h"
#include "DrawDebugHelpers.h"
#include "SActionComponent.h"
#include "SAttributeComponent.h"
#include "SWorldUserWidget.h"
#include "AI/SAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
 	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");
	//GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	SetReplicates(true);

}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComp->OnSeePawn.AddDynamic(this,&ASAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &ASAICharacter::OnHealthChanged);
}

void ASAICharacter::SetTargetActor(AActor* NewTarget)
{
	if(AAIController* AIC = Cast<AAIController>(GetController()))
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
}

AActor* ASAICharacter::GetTargetActor()
{
	if(AAIController* AIC = Cast<AAIController>(GetController()))
		return Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("TargetActor"));

	return nullptr;
}

void ASAICharacter::ShowSpottedWidget_Implementation()
{
	USWorldUserWidget* PlayerSpottedWidget = CreateWidget<USWorldUserWidget>(GetWorld(), PlayerSpottedWidgetClass);
	if(PlayerSpottedWidget)
	{
		PlayerSpottedWidget->AttachedActor = this;
		PlayerSpottedWidget->AddToViewport(2);
	}
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	if(Pawn == GetTargetActor())
		return;
	
	SetTargetActor(Pawn);
	ShowSpottedWidget();
	/*USWorldUserWidget* PlayerSpottedWidget = CreateWidget<USWorldUserWidget>(GetWorld(), PlayerSpottedWidgetClass);
	if(PlayerSpottedWidget)
	{
		PlayerSpottedWidget->AttachedActor = this;
		PlayerSpottedWidget->AddToViewport(2);
	}*/
	//DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
}

void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	if(Delta<0.0f)
	{
		if(InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}

		if(!ActiveHealthBar)
		{
			ActiveHealthBar = CreateWidget<USWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
			if(ActiveHealthBar)
			{
				ActiveHealthBar->AttachedActor = this;
				ActiveHealthBar->AddToViewport();
			}
		}
		
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
		
		if(NewHealth <= 0.0f)
		{
			AAIController* AIC = Cast<AAIController>(GetController());
			if(AIC)
				AIC->GetBrainComponent()->StopLogic("Killed");

			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();
			
			SetLifeSpan(10.0f);
		}
	}
}
