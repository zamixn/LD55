// Fill out your copyright notice in the Description page of Project Settings.


#include "ProficiencyScreen.h"

#include "ProficiencyCard.h"
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
