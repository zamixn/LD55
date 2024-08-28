// Fill out your copyright notice in the Description page of Project Settings.


#include "InfectedCounter.h"

#include "Components/TextBlock.h"

void UInfectedCounter::UpdateInfected(const int32 TotalInfectedValue, const int32 LeftUntilLevelUp, const int32 Level) const
{
	if(!TotalInfected || !Lvl || !LeftUntilLvlUp)
	{
		return;
	}

	TotalInfected->SetText(FText::Format(FText::FromString(TEXT("Infected: {0}")), TotalInfectedValue));
	LeftUntilLvlUp->SetText(FText::Format(FText::FromString(TEXT("Left until plague up: {0}")), LeftUntilLevelUp));
	Lvl->SetText(FText::Format(FText::FromString(TEXT("Plague level: {0}")), Level));
}
