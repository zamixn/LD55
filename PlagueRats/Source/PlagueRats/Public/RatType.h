#pragma once

#include "CoreMinimal.h"
#include "RatType.generated.h"

UENUM(BlueprintType)
enum class ERatType : uint8
{
	Undefined = 0,
	BasicRat = 1,
	BigRat = 2,
	Max
};