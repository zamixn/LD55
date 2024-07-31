#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProficiancyType.h"
#include "ProficiancyCard.generated.h"

UCLASS()
class PLAGUERATS_API UProficiancyCard : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetType(const EProficiancyType& type);

	void SetCallback(FProficiancyClickCallback callback);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateText(const EProficiancyType& type);

	UPROPERTY(BlueprintReadWrite)
	EProficiancyType CurrentType;

protected:
	UFUNCTION(BlueprintCallable)
	void OnClick();

private:

	FProficiancyClickCallback ClickCallback;
};
