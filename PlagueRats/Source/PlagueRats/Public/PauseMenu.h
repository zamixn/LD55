// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PLAGUERATS_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void Show(const bool bDead);

	UFUNCTION()
	void OnResumeClicked();

	UFUNCTION()
	void OnQuitClicked();

protected:
	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> TitleText = nullptr;

	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> ScoreText = nullptr;

	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UButton> ResumeButton = nullptr;

	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	TObjectPtr<UButton> QuitButton = nullptr;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MainMenuLevel = nullptr;
};
