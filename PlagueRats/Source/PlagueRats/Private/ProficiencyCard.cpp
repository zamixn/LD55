// Fill out your copyright notice in the Description page of Project Settings.


#include "ProficiencyCard.h"

#include "Components/TextBlock.h"

void UProficiencyCard::RollRandomType()
{
	SetType(static_cast<EProficiencyCardType>(FMath::RandRange(0, static_cast<int32>(EProficiencyCardType::Max) - 1)));
}

void UProficiencyCard::SetController(UProficiencyScreen* NewProficiencyScreen)
{
	ProficiencyScreen = NewProficiencyScreen;
}

void UProficiencyCard::SetType(const EProficiencyCardType NewType)
{
	Type = NewType;
	switch (Type)
	{
	case EProficiencyCardType::RatLifeTime:
		TitleText->SetText(FText::FromString(TEXT("Vermin Vitality")));
		DescriptionText->SetText(FText::FromString(TEXT("+1s to rat lifetime")));
		break;
	case EProficiencyCardType::ManaRecovery:
		TitleText->SetText(FText::FromString(TEXT("Channeling")));
		DescriptionText->SetText(FText::FromString(TEXT("+10% faster mana regen on each infection")));
		break;
	case EProficiencyCardType::RatCount:
		TitleText->SetText(FText::FromString(TEXT("Summoner")));
		DescriptionText->SetText(FText::FromString(TEXT("+1 rat on each summoning ritual")));
		break;
	case EProficiencyCardType::RatSpeed:
		TitleText->SetText(FText::FromString(TEXT("Vermin Agility")));
		DescriptionText->SetText(FText::FromString(TEXT("+50cm/s to rat speed")));
		break;
	case EProficiencyCardType::TotalMana:
		TitleText->SetText(FText::FromString(TEXT("Reserves")));
		DescriptionText->SetText(FText::FromString(TEXT("+10 mana")));
		break;
	default:
		break;
	}
}