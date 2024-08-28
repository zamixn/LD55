// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"

#include "PauseMenu.h"
#include "ProficiencyScreen.h"
#include "WidgetHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	GameHud = Cast<UWidgetHUD>(UWidgetBlueprintLibrary::Create(this, HudToCreate, nullptr));
	if(GameHud)
	{
		GameHud->AddToViewport();
		ManaBar = GameHud->ManaBar;
		InfectedCounter = GameHud->InfectedCounter;
	}

	ProficiencyScreen = Cast<UProficiencyScreen>(UWidgetBlueprintLibrary::Create(this, ProficiencyScreenToCreate, nullptr));
	PauseMenu = Cast<UPauseMenu>(UWidgetBlueprintLibrary::Create(this, PauseMenuToCreate, nullptr));
}
