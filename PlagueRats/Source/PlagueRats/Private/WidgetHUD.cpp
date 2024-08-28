// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHUD.h"

#include "RatSelector.h"

void UWidgetHUD::UnlockRat(const ERatType ratType) const
{
	for (size_t i = 0; i < RatSelectors.Num(); i++)
	{
		if (RatSelectors[i]->RatType == ratType)
			RatSelectors[i]->SetVisibility(ESlateVisibility::Visible);
	}
}

void UWidgetHUD::UpdateRatSelectors() const
{
	for (size_t i = 0; i < RatSelectors.Num(); i++)
	{
		RatSelectors[i]->UpdateSelector();
	}
}

void UWidgetHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	for (size_t i = 1; i < RatSelectors.Num(); i++)
	{
		RatSelectors[i]->SetVisibility(ESlateVisibility::Collapsed);
	}
}
