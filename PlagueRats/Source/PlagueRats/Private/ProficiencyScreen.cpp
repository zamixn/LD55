// Fill out your copyright notice in the Description page of Project Settings.


#include "ProficiencyScreen.h"

#include "ProficiencyCard.h"
#include "RatPlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UProficiencyScreen::Show(const int32 CurrentLvl)
{
	AddToViewport();
	
	ProficiencyCard1->RollRandomType();
	ProficiencyCard2->RollRandomType();
	ProficiencyCard3->RollRandomType();

	ProficiencyCard1->SetController(this);
	ProficiencyCard2->SetController(this);
	ProficiencyCard3->SetController(this);

	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetOwningPlayer(), nullptr, EMouseLockMode::LockAlways);
	UGameplayStatics::SetGamePaused(this, true);

	if(const FText* UnlockText = RatUnlockTextMap.Find(CurrentLvl))
	{
		RatUnlockText->SetText(*UnlockText);
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
