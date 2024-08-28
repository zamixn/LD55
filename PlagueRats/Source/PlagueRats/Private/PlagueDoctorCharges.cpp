// Fill out your copyright notice in the Description page of Project Settings.


#include "PlagueDoctorCharges.h"

#include "Components/TextBlock.h"

void UPlagueDoctorCharges::UpdateCharges(const int32 NewCharges) const
{
	if(!ChargesLeft)
	{
		return;
	}

	ChargesLeft->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewCharges)));
}
