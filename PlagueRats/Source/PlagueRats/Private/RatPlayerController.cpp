// Fill out your copyright notice in the Description page of Project Settings.


#include "RatPlayerController.h"

#include "BaseHUD.h"
#include "BaseRat.h"
#include "InfectedCounter.h"
#include "ManaBar.h"
#include "PauseMenu.h"
#include "ProficiencyScreen.h"
#include "WidgetHUD.h"
#include "Kismet/GameplayStatics.h"

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

void ARatPlayerController::OnRatDeath() const
{
	if(CurrentMana < RatSpawnCost && !CheckIfThereAreAliveRats())
	{
		if(const ABaseHUD* BaseHUD = GetHUD<ABaseHUD>())
		{
			if(BaseHUD->PauseMenu)
			{
				BaseHUD->PauseMenu->Show(true);
			}
		}
	}
}

void ARatPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CurrentMana = MaxMana;
	GetWorldTimerManager().SetTimerForNextTick(this, &ARatPlayerController::SetupStats);
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

	if(const ABaseHUD* PlayerHUD = GetHUD<ABaseHUD>())
	{
		if(PlayerHUD->ProficiencyScreen)
		{
			PlayerHUD->ProficiencyScreen->Show(CurrentLvl);
		}

		if(CurrentLvl == BigRatUnlockLevel && PlayerHUD->GameHud)
		{
			PlayerHUD->GameHud->UnlockBigRat();
		}
	}
}

bool ARatPlayerController::CheckIfThereAreAliveRats() const
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, ABaseRat::StaticClass(), OutActors);

	for(const AActor* Actor : OutActors)
	{
		if(const ABaseRat* Rat = Cast<ABaseRat>(Actor))
		{
			if(!Rat->IsDead())
			{
				return true;
			}
		}
	}

	return false;
}

void ARatPlayerController::SetupStats() const
{
	if(const ABaseHUD* PlayerHUD = GetHUD<ABaseHUD>())
	{
		if(PlayerHUD->ManaBar)
		{
			PlayerHUD->ManaBar->UpdateMana(CurrentMana, MaxMana);
		}

		if(PlayerHUD->InfectedCounter)
		{
			PlayerHUD->InfectedCounter->UpdateInfected(TotalInfected, InfectedNeededForLvl, CurrentLvl);
		}
	}
}
