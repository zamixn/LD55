#include "ProficiancyScreen.h"
#include "Math/UnrealMathUtility.h"

void UProficiancyScreen::ShowProficiancyCards()
{
	TArray<EProficiancyType> types;
	RollRandomProficiancies(ProficiancyCards.Num(), types);

	for (size_t i = 0; i < ProficiancyCards.Num(); i++)
	{
		UProficiancyCard* card = ProficiancyCards[i];
		EProficiancyType type = types[i];
		card->SetType(type);
		FProficiancyClickCallback callback;
		callback.BindLambda([this] (EProficiancyType clickedType)
			{
				OnProficiancyClicked(clickedType);
			});
		card->SetCallback(callback);
	}
}

void UProficiancyScreen::RollRandomProficiancies(const int32 NumOfProficiancies, TArray<EProficiancyType>& OutTypes)
{
	TArray<EProficiancyType> validTypes;
	for (uint8 i = (uint8)EProficiancyType::Undefined + 1; i < (uint8)EProficiancyType::Max; i++)
	{
		EProficiancyType t = (EProficiancyType)i;
		validTypes.Add(t);
	}

	if (validTypes.Num() < NumOfProficiancies)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried rolling more proficiancies than available"));
	}

	for (size_t i = 0; i < NumOfProficiancies && validTypes.Num() > 0; ++i)
	{
		int32 rand = FMath::RandRange(0, validTypes.Num() - 1);

		EProficiancyType t = validTypes[rand];
		validTypes.RemoveAt(rand);
		OutTypes.Add(t);
	}
}
