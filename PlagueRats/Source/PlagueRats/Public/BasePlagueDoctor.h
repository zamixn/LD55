// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "BasePlagueDoctor.generated.h"

class UNiagaraComponent;
class USphereComponent;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class PLAGUERATS_API ABasePlagueDoctor : public ABaseEnemy
{
	GENERATED_BODY()

public:
	ABasePlagueDoctor();

	UFUNCTION()
	void OnDamageSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
							   const FHitResult& SweepResult);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> ChargesLeft = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> DamageSphere = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> DamageParticles = nullptr;

	UPROPERTY(EditAnywhere)
	int32 NumberOfChargesLeft = 10;

private:
	void Die();
	void CleanUpAfterDeath();
};
