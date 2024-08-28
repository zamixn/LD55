#include "PlagueStaticFunctions.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogRatPlague);

APlagueGameMode* PlagueStaticFunctions::GetGameMode(const UObject* WorldContextObject)
{
	APlagueGameMode* gamemode = Cast<APlagueGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!gamemode)
	{
		UE_LOG(LogRatPlague, Error, TEXT("PlagueGameMode is invalid"));
	}
	return gamemode;
}
