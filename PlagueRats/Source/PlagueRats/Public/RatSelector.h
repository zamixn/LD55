// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RatType.h"
#include "Blueprint/UserWidget.h"
#include "RatSelector.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class PLAGUERATS_API URatSelector : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	void UpdateSelector() const;

	UFUNCTION()
	void OnRatButtonClicked();

	UPROPERTY(EditAnywhere)
	ERatType RatType = ERatType::BasicRat;
	
protected:
	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UButton> RatButton = nullptr;

	UPROPERTY(EditAnywhere)
	FSlateColor DefaultTint;

	UPROPERTY(EditAnywhere)
	FSlateColor SelectedTint;

private:
	FSlateBrush CreateSlateBrushFromTexture(const FSlateBrush& RefBrush, UTexture2D* Texture) const;
	bool IsSelectedRatType() const;
};
