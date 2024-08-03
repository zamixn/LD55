// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseVillager.generated.h"

class ABaseVillagerSpawner;
class UWidgetComponent;

UCLASS()
class PLAGUERATS_API ABaseVillager : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseVillager();

	UPROPERTY()
	TObjectPtr<ABaseVillagerSpawner> Spawner = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> SpeechBubble = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> PlagueCounter = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<USoundCue*> DeathNoises;

	UPROPERTY(EditAnywhere)
	float TimeUntilHide = 3.f;

	UPROPERTY(EditAnywhere)
	float TimeUntilDestroy = 10.f;

public:	
	FORCEINLINE bool IsDead() const { return bIsDead; }
	void IncreasePlagueCounter();

private:
	void Die();
	void DestroyVillager();
	void HideVillager();
	void CleanupAfterDeath();
	
	bool bIsDead = false;
	int32 LevelOfInfection = 0;
	FTimerHandle HideVillagerHandle;
	FTimerHandle DestroyVillagerHandle;
};
