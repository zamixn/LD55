#include "PlagueStaticFunctions.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogRatPlague);

APlagueGameMode* PlagueStaticFunctions::GetGameMode(const UObject* WorldContextObject)
{
	APlagueGameMode* Gamemode = Cast<APlagueGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!Gamemode)
	{
		UE_LOG(LogRatPlague, Error, TEXT("PlagueGameMode is invalid"));
	}
	return Gamemode;
}
