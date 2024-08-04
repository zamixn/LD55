// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RatPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PLAGUERATS_API ARatPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void OnRatAttackedVillager(const bool bHasKilled);
	void OnRatDeath() const;
	FORCEINLINE int32 GetTotalInfected() const { return TotalInfected; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RatSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RatLifetime = 0.f;

	UPROPERTY(BlueprintReadWrite)
	int32 DaysSurvived = 0;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentMana = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMana = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ManaGainedPerRatAttack = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ManaRecovery = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RatSpawnCost = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InfectedNeededForLvl = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BaseInfectedNeededForLvl = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BigRatUnlockLevel = 5;

private:
	void OnRatKilledVillager();
	void LevelUp();
	bool CheckIfThereAreAliveRats() const;
	void SetupStats() const;

	int32 TotalInfected = 0.f;
	int32 CurrentLvl = 0;
};
