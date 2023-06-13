#include "SAction_ProjectileAttack.h"

#include "SCharacter.h"
#include "Kismet/GameplayStatics.h"

USAction_ProjectileAttack::USAction_ProjectileAttack()
{
}

void USAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if(ACharacter* Character = Cast<ACharacter>(Instigator))
	{
		Character->PlayAnimMontage(AttackAnim);
		UGameplayStatics::SpawnEmitterAttached(CastingEffect, Character->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, "AttackDelay_Elapsed", Character);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, TimerDelegate, AttackAnimDelay, false);
	}
}

void USAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	if (ensureAlways(ProjectileClass))
	{
		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);
		
		//Calculate impact rotation - line trace
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
		// Ignore Player
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(InstigatorCharacter);
		FCollisionShape Shape; Shape.SetSphere(20.0f);
		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation();
		FVector TraceEnd = InstigatorCharacter->GetPawnViewLocation() + (InstigatorCharacter->GetControlRotation().Vector() * 5000);
	
		FHitResult Hit;
		FRotator ProjRotation = GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, Shape, CollisionQueryParams) ?
			FRotationMatrix::MakeFromX(Hit.ImpactPoint-HandLocation).Rotator() : FRotationMatrix::MakeFromX(TraceEnd-HandLocation).Rotator();
	
		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}

	StopAction(InstigatorCharacter);
}