// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProficiencyCardType.h"
#include "Blueprint/UserWidget.h"
#include "ProficiencyScreen.generated.h"

class UTextBlock;
class UProficiencyCard;

/**
 * 
 */
UCLASS()
class PLAGUERATS_API UProficiencyScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	void Show(const int32 CurrentLvl);
	void Hide();
	void OnProficiencyClicked(EProficiencyCardType Type);

protected:
	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UProficiencyCard> ProficiencyCard1 = nullptr;

	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UProficiencyCard> ProficiencyCard2 = nullptr;

	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UProficiencyCard> ProficiencyCard3 = nullptr;

	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> RatUnlockText = nullptr;
};
