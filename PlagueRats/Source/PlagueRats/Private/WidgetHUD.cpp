// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHUD.h"

#include "RatSelector.h"

void UWidgetHUD::UnlockBigRat() const
{
	if(RatSelector)
	{
		RatSelector->SetVisibility(ESlateVisibility::Visible);
	}
}
