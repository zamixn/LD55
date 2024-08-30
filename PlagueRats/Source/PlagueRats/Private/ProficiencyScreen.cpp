// Fill out your copyright notice in the Description page of Project Settings.


#include "ProficiencyScreen.h"

#include "ProficiencyCard.h"
#include "RatPlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "PlagueGameMode.h"
#include "PlagueStaticFunctions.h"
#include "Kismet/GameplayStatics.h"

void UProficiencyScreen::Show(const int32 CurrentLvl)
{
	AddToViewport();
	
	TArray<EProficiencyCardType> types;
	RollRandomProficiencies(3, types);
	ProficiencyCard1->SetType(types[0]);
	ProficiencyCard2->SetType(types[1]);
	ProficiencyCard3->SetType(types[2]);

	ProficiencyCard1->SetController(this);
	ProficiencyCard2->SetController(this);
	ProficiencyCard3->SetController(this);

	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetOwningPlayer(), nullptr, EMouseLockMode::LockAlways);
	UGameplayStatics::SetGamePaused(this, true);

	const APlagueGameMode* Gamemode = PlagueStaticFunctions::GetGameMode(this);
	if (FUnlockableRatData ratUnlockableData; Gamemode->UnlockablesDataAsset->GetRatUnlockedForLevel(CurrentLvl, ratUnlockableData))
	{
		RatUnlockText->SetText(ratUnlockableData.UnlockText);
	}
}

void UProficiencyScreen::Hide()
{
	RemoveFromParent();
	if(ARatPlayerController* RatPlayerController = GetOwningPlayer<ARatPlayerController>())
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(RatPlayerController, nullptr, EMouseLockMode::LockAlways);
	}
}

void UProficiencyScreen::OnProficiencyClicked(const EProficiencyCardType Type)
{
	if(ARatPlayerController* RatPlayerController = GetOwningPlayer<ARatPlayerController>())
	{
		RatPlayerController->GrantProficiency(Type);
		Hide();
		UGameplayStatics::SetGamePaused(this, false);
	}
}

void UProficiencyScreen::RollRandomProficiencies(const int32 NumOfProficiancies, TArray<EProficiencyCardType>& OutTypes)
{
	TArray<EProficiencyCardType> validTypes;
	for (uint8 i = 0; i < (uint8)EProficiencyCardType::Max; i++)
	{
		EProficiencyCardType t = (EProficiencyCardType)i;
		validTypes.Add(t);
	}

	if (validTypes.Num() < NumOfProficiancies)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried rolling more proficiancies than available"));
	}

	for (size_t i = 0; i < NumOfProficiancies && validTypes.Num() > 0; ++i)
	{
		int32 rand = FMath::RandRange(0, validTypes.Num() - 1);

		EProficiencyCardType t = validTypes[rand];
		validTypes.RemoveAt(rand);
		OutTypes.Add(t);
	}
}