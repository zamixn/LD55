// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVillager.h"

#include "PlagueBar.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ABaseVillager::ABaseVillager()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpeechBubble = CreateDefaultSubobject<UWidgetComponent>(TEXT("SpeechBubble"));
	SpeechBubble->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ABaseVillager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseVillager::IncreasePlagueCounter()
{
	++LevelOfInfection;
	if(UPlagueBar* PlagueBar = Cast<UPlagueBar>(PlagueCounter->GetWidget()))
	{
		PlagueBar->ChangePlagueVisuals(LevelOfInfection);
	}

	if(LevelOfInfection >= 3)
	{
		
	}
}

