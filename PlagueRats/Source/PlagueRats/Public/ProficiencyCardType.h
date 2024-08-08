#pragma once

UENUM(BlueprintType)
enum class EProficiencyCardType : uint8
{
	RatLifeTime,
	RatSpeed,
	RatCount,
	TotalMana,
	ManaRecovery,
	Max UMETA(Hidden)
};
