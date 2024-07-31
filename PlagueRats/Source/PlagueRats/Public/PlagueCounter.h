// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlagueCounter.generated.h"

class UBorder;

/**
 * 
 */
UCLASS()
class PLAGUERATS_API UPlagueCounter : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UBorder> VisualBar = nullptr;
};
