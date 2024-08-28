// Fill out your copyright notice in the Description page of Project Settings.


#include "ManaBar.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UManaBar::UpdateMana(const float CurrentMana, const float MaxMana) const
{
	if(!Text || !ProgressBar || MaxMana == 0)
	{
		return;
	}

	ProgressBar->SetPercent(CurrentMana / MaxMana);
	Text->SetText(FText::Format(FText::FromString(TEXT("{0}/{1}")), CurrentMana, MaxMana));
}
