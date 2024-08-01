#pragma once

#include "CoreMinimal.h"
#include "ProficiancyType.generated.h"

UENUM(BlueprintType)
enum class EProficiancyType : uint8
{
	Undefined = 0,
	RatLifeTime = 1,
	RatSpeed = 2,
	RatCount = 3,
	TotalMana = 4,
	ManaRecovery = 5,
	Max
};

DECLARE_DELEGATE_OneParam(FProficiancyClickCallback, EProficiancyType)