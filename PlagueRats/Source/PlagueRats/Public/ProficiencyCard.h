// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProficiencyCard.generated.h"

class UProficiencyScreen;
class UTextBlock;

UENUM(BlueprintType)
enum class EProficiencyCardType : uint8
{
	RatLifeTime,
	RatSpeed,
	RatCount,
	TotalMana,
	ManaRecovery,
	Max UMETA(Hidden)
};

/**
 * 
 */
UCLASS()
class PLAGUERATS_API UProficiencyCard : public UUserWidget
{
	GENERATED_BODY()

public:
	void RollRandomType();
	FORCEINLINE void SetController(UProficiencyScreen* NewProficiencyScreen);

protected:
	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> TitleText = nullptr;

	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> DescriptionText = nullptr;

	UPROPERTY()
	TObjectPtr<UProficiencyScreen> ProficiencyScreen = nullptr;

private:
	void SetType(EProficiencyCardType NewType);

	EProficiencyCardType Type = EProficiencyCardType::RatLifeTime;
};
