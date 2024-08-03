// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

class UPauseMenu;
class UProficiencyScreen;
class UInfectedCounter;
class UManaBar;
class UWidgetHUD;

/**
 * 
 */
UCLASS()
class PLAGUERATS_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UManaBar> ManaBar = nullptr;

	UPROPERTY()
	TObjectPtr<UInfectedCounter> InfectedCounter = nullptr;

	UPROPERTY()
	TObjectPtr<UProficiencyScreen> ProficiencyScreen = nullptr;

	UPROPERTY()
	TObjectPtr<UWidgetHUD> GameHud = nullptr;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HudToCreate = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ProficiencyScreenToCreate = nullptr;

	UPROPERTY()
	TObjectPtr<UPauseMenu> PauseMenu = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PauseMenuToCreate = nullptr;
};
