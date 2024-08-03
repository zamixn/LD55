// Fill out your copyright notice in the Description page of Project Settings.


#include "RatPlayerController.h"

#include "BaseHUD.h"
#include "InfectedCounter.h"
#include "ManaBar.h"

void ARatPlayerController::OnRatAttackedVillager(const bool bHasKilled)
{
	CurrentMana = FMath::Clamp(CurrentMana + ManaGainedPerRatAttack * ManaRecovery, 0.f, MaxMana);

	if(bHasKilled)
	{
		OnRatKilledVillager();
	}

	if(const ABaseHUD* PlayerHUD = GetHUD<ABaseHUD>())
	{
		if(PlayerHUD->ManaBar)
		{
			PlayerHUD->ManaBar->UpdateMana(CurrentMana, MaxMana);
		}
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

	if(const ABaseHUD* PlayerHUD = GetHUD<ABaseHUD>())
	{
		if(PlayerHUD->InfectedCounter)
		{
			PlayerHUD->InfectedCounter->UpdateInfected(TotalInfected, InfectedNeededForLvl, CurrentLvl);
		}
	}
}

void ARatPlayerController::LevelUp()
{
	InfectedNeededForLvl = 2 * CurrentLvl + BaseInfectedNeededForLvl;
	++CurrentLvl;
	
}
