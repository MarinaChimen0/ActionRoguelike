#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USActionComponent;
class USAttributeComponent;
class USInteractionComponent;
class UCameraComponent;
class USpringArmComponent;
class UParticleSystem;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USAttributeComponent* AttributeComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USActionComponent* ActionComp;

	virtual void PostInitializeComponents() override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void SprintStart();
	void SprintStop();
	void PrimaryInteract();
	void PrimaryAttack();
	void BlackHoleAttack();
	void Dash();

	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual FVector GetPawnViewLocation() const override;
	
public:
	
	// Sets default values for this character's properties
	ASCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);
};
