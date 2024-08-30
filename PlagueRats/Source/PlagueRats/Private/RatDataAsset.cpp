#include "RatDataAsset.h"

bool URatDataAsset::GetRatOfType(const ERatType ratType, FRatData & ratData)
{
	if (RatDatas.Contains(ratType))
	{
		ratData = RatDatas[ratType];
		return true;
	}
	return false;
}
