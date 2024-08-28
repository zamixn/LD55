// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlagueDoctorCharges.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PLAGUERATS_API UPlagueDoctorCharges : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateCharges(const int32 NewCharges) const;

protected:
	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> ChargesLeft = nullptr;
};
