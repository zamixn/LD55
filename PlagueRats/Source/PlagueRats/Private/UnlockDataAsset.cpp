#include "UnlockDataAsset.h"

bool UUnlockDataAsset::GetRatUnlockedForLevel(const int32 level, FUnlockableRatData& unlockedRatData)
{
	for (size_t i = 0; i < UnlockableRats.Num(); i++)
	{
		const FUnlockableRatData& data = UnlockableRats[i];
		if (data.UnlockLevel == level)
		{
			unlockedRatData = data;
			return true;
		}
	}
	return false;
}
