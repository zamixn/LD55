// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProficiencyCardType.h"
#include "Blueprint/UserWidget.h"
#include "ProficiencyCard.generated.h"

class UButton;
class UProficiencyScreen;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PLAGUERATS_API UProficiencyCard : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void RollRandomType();
	FORCEINLINE void SetController(UProficiencyScreen* NewProficiencyScreen);

	UFUNCTION()
	void OnProficiencyButtonClicked();

protected:
	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> TitleText = nullptr;

	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> DescriptionText = nullptr;

	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UButton> ProficiencyButton = nullptr;

	UPROPERTY()
	TObjectPtr<UProficiencyScreen> ProficiencyScreen = nullptr;

private:
	void SetType(EProficiencyCardType NewType);

	EProficiencyCardType Type = EProficiencyCardType::RatLifeTime;
};
