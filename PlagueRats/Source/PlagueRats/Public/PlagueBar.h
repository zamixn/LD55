// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlagueBar.generated.h"

class UHorizontalBox;
/**
 * 
 */
UCLASS()
class PLAGUERATS_API UPlagueBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void ChangePlagueVisuals(const int32 IndexOfPlague);
	
protected:
	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UHorizontalBox> PlagueContainer = nullptr;

private:
	bool bWasShown = false;
};
