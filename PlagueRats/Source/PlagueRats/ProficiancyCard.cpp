#include "ProficiancyCard.h"

void UProficiancyCard::SetType(const EProficiancyType& type)
{
	CurrentType = type;
	UpdateText(CurrentType);
}

void UProficiancyCard::SetCallback(FProficiancyClickCallback callback)
{
	ClickCallback = callback;
}

void UProficiancyCard::OnClick()
{
	ClickCallback.ExecuteIfBound(CurrentType);
}
