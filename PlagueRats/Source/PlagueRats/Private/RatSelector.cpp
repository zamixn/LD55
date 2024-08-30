// Fill out your copyright notice in the Description page of Project Settings.


#include "RatSelector.h"

#include "PlagueStaticFunctions.h"
#include "RatPlayerController.h"
#include "Components/Button.h"

void URatSelector::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateSelector();
	if(RatButton)
	{
		RatButton->OnClicked.AddUniqueDynamic(this, &URatSelector::OnRatButtonClicked);
	}
}

void URatSelector::UpdateSelector() const
{
	if(!RatButton)
	{
		return;
	}

	FRatData ratData;
	PlagueStaticFunctions::GetGameMode(this)->RatDataAsset->GetRatOfType(RatType, ratData);
	UTexture2D* TextureToSet = ratData.Icon.LoadSynchronous();

	FButtonStyle ButtonStyle = RatButton->GetStyle();
	ButtonStyle.SetNormal(CreateSlateBrushFromTexture(ButtonStyle.Normal, TextureToSet));
	ButtonStyle.SetHovered(CreateSlateBrushFromTexture(ButtonStyle.Hovered, TextureToSet));
	ButtonStyle.SetPressed(CreateSlateBrushFromTexture(ButtonStyle.Pressed, TextureToSet));
	ButtonStyle.SetDisabled(CreateSlateBrushFromTexture(ButtonStyle.Disabled, TextureToSet));
	RatButton->SetStyle(ButtonStyle);
}

void URatSelector::OnRatButtonClicked()
{
	if(ARatPlayerController* RatPlayerController = GetOwningPlayer<ARatPlayerController>())
	{
		RatPlayerController->SelectRatType(RatType);
	}
}

FSlateBrush URatSelector::CreateSlateBrushFromTexture(const FSlateBrush& RefBrush, UTexture2D* Texture) const
{
	FSlateBrush SlateBrush;
	SlateBrush.DrawAs = ESlateBrushDrawType::Image;
	SlateBrush.Tiling = ESlateBrushTileType::NoTile;
	SlateBrush.Mirroring = ESlateBrushMirrorType::NoMirror;
	SlateBrush.SetImageSize(RefBrush.GetImageSize());
	SlateBrush.Margin = RefBrush.GetMargin();
	SlateBrush.TintColor = IsSelectedRatType() ? SelectedTint : DefaultTint;
	SlateBrush.OutlineSettings = RefBrush.OutlineSettings;
	SlateBrush.SetResourceObject(Texture);
	return SlateBrush;
}

bool URatSelector::IsSelectedRatType() const
{
	if(const ARatPlayerController* RatPlayerController = GetOwningPlayer<ARatPlayerController>())
	{
		return RatPlayerController->CurrentRatType == RatType;
	}

	return false;
}
