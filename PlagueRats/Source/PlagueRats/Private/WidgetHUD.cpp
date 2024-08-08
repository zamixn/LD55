// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHUD.h"

#include "RatSelector.h"

void UWidgetHUD::UnlockBigRat() const
{
	if(BigRatSelector)
	{
		BigRatSelector->SetVisibility(ESlateVisibility::Visible);
	}
}

void UWidgetHUD::UpdateRatSelectors() const
{
	if(SmallRatSelector)
	{
		SmallRatSelector->UpdateSelector();
	}

	if(BigRatSelector)
	{
		BigRatSelector->UpdateSelector();
	}
}
