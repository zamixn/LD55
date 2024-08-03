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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentMana = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMana = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ManaGainedPerRatAttack = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ManaRecovery = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InfectedNeededForLvl = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BaseInfectedNeededForLvl = 3;
	
public:
	void OnRatAttackedVillager(const bool bHasKilled);

private:
	void OnRatKilledVillager();
	void LevelUp();

	int32 TotalInfected = 0.f;
	int32 CurrentLvl = 0;
};
