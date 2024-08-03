// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InfectedCounter.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PLAGUERATS_API UInfectedCounter : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateInfected(const int32 TotalInfectedValue, const int32 LeftUntilLevelUp, const int32 Level) const;
	
protected:
	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> TotalInfected = nullptr;

	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> Lvl = nullptr;

	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> LeftUntilLvlUp = nullptr;
};
