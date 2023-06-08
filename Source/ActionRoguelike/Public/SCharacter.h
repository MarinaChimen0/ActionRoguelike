// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

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
	
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay = 0.2f;
	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> MagicProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackHoleProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashProjectileClass;
	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnim;
	UPROPERTY(EditAnywhere, Category = "Attack")
	UParticleSystem* CastingEffect;
	
	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_BlackHoleAttack;
	FTimerHandle TimerHandle_Dash;

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USAttributeComponent* AttributeComp;

	virtual void PostInitializeComponents() override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void PrimaryInteract();
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void BlackHoleAttack();
	void BlackHoleAttack_TimeElapsed();
	void Dash();
	void Dash_TimeElapsed();
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);
};
