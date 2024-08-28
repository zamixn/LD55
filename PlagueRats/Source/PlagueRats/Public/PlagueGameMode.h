#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "UnlockablesDataAsset.h"
#include "PlagueGameMode.generated.h"

UCLASS()
class PLAGUERATS_API APlagueGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UUnlockablesDataAsset* UnlockablesDataAsset;
};
