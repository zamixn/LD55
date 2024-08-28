#pragma once

#include "CoreMinimal.h"
#include "PlagueGameMode.h"

DECLARE_LOG_CATEGORY_EXTERN(LogRatPlague, Log, All);

class PLAGUERATS_API PlagueStaticFunctions
{
public:
	static APlagueGameMode* GetGameMode(const UObject* WorldContextObject);
};
