// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

class ABaseVillagerSpawner;

UCLASS()
class PLAGUERATS_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

	UPROPERTY()
	TObjectPtr<ABaseVillagerSpawner> Spawner = nullptr;
};
