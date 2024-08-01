#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RatType.h"
#include "UnlockDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FUnlockableRatData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UnlockLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERatType RatToUnlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText UnlockText;
};

UCLASS()
class PLAGUERATS_API UUnlockDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	bool GetRatUnlockedForLevel(const int32 level, FUnlockableRatData& unlockedRatData);

	UPROPERTY(EditAnywhere)
	TArray<FUnlockableRatData> UnlockableRats;
};

