// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITypes.h"
#include "GameFramework/Character.h"
#include "BaseVillager.generated.h"

class ABaseVillagerSpawner;
class UWidgetComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogVillager, Log, All);

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

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstance*> Skins;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimationAsset> WalkAnimation = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimationAsset> IdleAnimation = nullptr;

	UPROPERTY(EditAnywhere)
	float RoamAcceptanceRadius = 5.f;

	UPROPERTY(EditAnywhere)
	float MinWaitTime = 1.f;

	UPROPERTY(EditAnywhere)
	float MaxWaitTime = 3.f;

public:	
	FORCEINLINE bool IsDead() const { return bIsDead; }
	void IncreasePlagueCounter();

private:
	UFUNCTION()
	void OnMoveComplete(FAIRequestID RequestID, EPathFollowingResult::Type Result);

	void Die();
	void DestroyVillager();
	void HideVillager();
	void CleanupAfterDeath();
	void SetRandomSkin();
	void Roam();
	
	bool bIsDead = false;
	int32 LevelOfInfection = 0;
	FVector RoamOriginPoint = FVector::ZeroVector;
	float RoamRadius = 0.f;
	
	FTimerHandle HideVillagerHandle;
	FTimerHandle DestroyVillagerHandle;
	FTimerHandle IdleHandle;
};
