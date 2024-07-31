// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseVillager.generated.h"

class UWidgetComponent;

UCLASS()
class PLAGUERATS_API ABaseVillager : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseVillager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> SpeechBubble = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> PlagueCounter = nullptr;

public:	
	FORCEINLINE bool IsDead() const { return bIsDead; }
	void IncreasePlagueCounter();

private:
	bool bIsDead = false;
	int32 LevelOfInfection = 0;
};
