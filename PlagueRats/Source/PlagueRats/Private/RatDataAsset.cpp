#include "RatDataAsset.h"

bool URatDataAsset::GetRatOfType(const ERatType ratType, FRatData& ratData)
{
	if (ratType == ERatType::Undefined || ratType == ERatType::Max)
		return false;

	if (RatDatas.Contains(ratType))
	{
		ratData = RatDatas[ratType];
		return true;
	}
	return false;
}
