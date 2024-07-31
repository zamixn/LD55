// Fill out your copyright notice in the Description page of Project Settings.


#include "PlagueBar.h"

#include "PlagueCounter.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"

void UPlagueBar::ChangePlagueVisuals(const int32 IndexOfPlague)
{
	if(!PlagueContainer)
	{
		return;
	}

	if(const UPlagueCounter* PlagueCounter = Cast<UPlagueCounter>(PlagueContainer->GetChildAt(IndexOfPlague - 1)))
	{
		if(PlagueCounter->VisualBar)
		{
			PlagueCounter->VisualBar->SetBrushColor(FLinearColor(0.f, 1.f, 0.f, 0.8f));
		}
	}

	if(!bWasShown)
	{
		bWasShown = true;
		SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}
