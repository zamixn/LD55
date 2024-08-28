// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"

#include "RatPlayerController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if(ResumeButton)
	{
		ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::OnResumeClicked);
	}

	if(QuitButton)
	{
		QuitButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::OnQuitClicked);
	}
}

void UPauseMenu::Show(const bool bDead)
{
	if(!TitleText || !ScoreText || !ResumeButton)
	{
		return;
	}

	if(bDead)
	{
		TitleText->SetText(FText::FromString(TEXT("No Mana Left! You Died.")));
		if(const ARatPlayerController* PlayerController = GetOwningPlayer<ARatPlayerController>())
		{
			const FText Format = FText::FromString(TEXT("Final score: {0} villagers infected, {1} day(s) survived"));
			ScoreText->SetText(FText::Format(Format, PlayerController->GetTotalInfected(), PlayerController->DaysSurvived));
		}
	}
	else
	{
		TitleText->SetText(FText::FromString(TEXT("Paused")));
		ScoreText->SetText(FText::FromString(TEXT("")));
	}

	AddToViewport(999);
	UGameplayStatics::SetGamePaused(this, true);
	ResumeButton->SetVisibility(bDead ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
}

void UPauseMenu::OnResumeClicked()
{
	UGameplayStatics::SetGamePaused(this, false);
	RemoveFromParent();
}

void UPauseMenu::OnQuitClicked()
{
	UGameplayStatics::SetGamePaused(this, false);
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, MainMenuLevel);
}
