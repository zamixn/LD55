// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetHUD.generated.h"

class URatSelector;
class UInfectedCounter;
class UManaBar;

/**
 * 
 */
UCLASS()
class PLAGUERATS_API UWidgetHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void UnlockBigRat() const;
	
	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UManaBar> ManaBar = nullptr;

	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UInfectedCounter> InfectedCounter = nullptr;

	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<URatSelector> RatSelector = nullptr;
};
