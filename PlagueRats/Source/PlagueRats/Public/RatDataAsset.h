#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RatType.h"
#include "RatDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FRatData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERatType RatType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseRat> ClassToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon;
};

UCLASS()
class PLAGUERATS_API URatDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ERatType, FRatData> RatDatas;

	UFUNCTION(BlueprintCallable)
	bool GetRatOfType(const ERatType ratType, FRatData& ratData);
};
