// Fill out your copyright notice in the Description page of Project Settings.


#include "RatPlayerController.h"

void ARatPlayerController::OnRatAttackedVillager(const bool bHasKilled)
{
	CurrentMana = FMath::Clamp(CurrentMana + ManaGainedPerRatAttack * ManaRecovery, 0.f, MaxMana);

	if(bHasKilled)
	{
		OnRatKilledVillager();
	}
}

void ARatPlayerController::OnRatKilledVillager()
{
	CurrentMana = FMath::Clamp(CurrentMana + ManaGainedPerRatAttack * ManaRecovery, 0.f, MaxMana);
	
	++TotalInfected;
	if(--InfectedNeededForLvl <= 0)
	{
		LevelUp();
	}
}

void ARatPlayerController::LevelUp()
{
	InfectedNeededForLvl = 2 * CurrentLvl + BaseInfectedNeededForLvl;
	++CurrentLvl;
	
}
