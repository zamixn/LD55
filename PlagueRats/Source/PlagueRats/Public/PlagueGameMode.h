// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "UnlockDataAsset.h"
#include "RatDataAsset.h"
#include "PlagueGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLAGUERATS_API APlagueGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UUnlockDataAsset* UnlockDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	URatDataAsset* RatDataAsset;	
};
