#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProficiancyCard.h"
#include "ProficiancyType.h"
#include "ProficiancyScreen.generated.h"

UCLASS()
class PLAGUERATS_API UProficiancyScreen : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable)
	void ShowProficiancyCards();

	UFUNCTION(BlueprintImplementableEvent)
	void OnProficiancyClicked(EProficiancyType type);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UProficiancyCard*> ProficiancyCards;

private:
	void RollRandomProficiancies(const int32 NumOfProficiancies, TArray<EProficiancyType>& OutTypes);
};
