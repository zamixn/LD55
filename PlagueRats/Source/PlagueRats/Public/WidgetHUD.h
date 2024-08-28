// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RatType.h"
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
	void UnlockRat(const ERatType ratType) const;
	void UpdateRatSelectors() const;
	
	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UManaBar> ManaBar = nullptr;

	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UInfectedCounter> InfectedCounter = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (MakeEditWidget = true))
	TArray<TObjectPtr<URatSelector>> RatSelectors;

protected:
	virtual void NativeOnInitialized() override;
};
