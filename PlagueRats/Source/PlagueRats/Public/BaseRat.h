// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AITypes.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "BaseRat.generated.h"

class UNiagaraComponent;
class ABaseVillager;

UCLASS()
class PLAGUERATS_API ABaseRat : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseRat();

	UFUNCTION()
	void OnMoveComplete(FAIRequestID RequestID, EPathFollowingResult::Type Result);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetRatBigScale() const;
	void SetRatSmallScale() const;
	void TryAttackingVillager();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> DeathParticles = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> SpawnParticles = nullptr;

	UPROPERTY(EditAnywhere)
	FVector BigScaleToSet = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	FVector SmallScaleToSet = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	float MinTimeToWaitBeforeNextAttack = 0.5f;

	UPROPERTY(EditAnywhere)
	float MaxTimeToWaitBeforeNextAttack = 1.f;

	UPROPERTY(EditAnywhere)
	float TimeUntilNextAttackTry = 0.5f;
	
	UPROPERTY(EditAnywhere)
	float MovementSpeedMultiplier = 50.f;

	UPROPERTY(EditAnywhere)
	float MinAliveTime = 3.f;

	UPROPERTY(EditAnywhere)
	float MaxAliveTime = 5.f;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimationAsset> MeshAnimation = nullptr;
	
	TObjectPtr<ABaseVillager> CurrentTarget = nullptr;

private:
	void AttackVillager();
	ABaseVillager* GetClosestVillager() const;
	void ApplyStats() const;
	float GetAdditionalMoveSpeed() const;
	float GetAdditionalLifetime() const;
	void Die();
	
	TSet<ABaseVillager*> AttackedVillagers;
	bool bIsDead = false;
	FTimerHandle AttackHandle;
	FTimerHandle TryAttackingVillagerHandle;
	FTimerHandle DeathHandle;
};
