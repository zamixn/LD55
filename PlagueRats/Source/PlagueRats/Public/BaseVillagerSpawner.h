// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseVillagerSpawner.generated.h"

class ABaseEnemy;
class UBoxComponent;

UCLASS()
class PLAGUERATS_API ABaseVillagerSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseVillagerSpawner();

	FORCEINLINE void DecrementCurrentAmountOfVillagers() { --CurrentAmountOfVillagers; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void AttemptToSpawnVillagers();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> SpawnBounds = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseEnemy> VillagerClass = nullptr;

	UPROPERTY(EditAnywhere)
	int32 CurrentAmountOfVillagers = 0;

	UPROPERTY(EditAnywhere)
	int32 AmountToKeepAlive = 3;

	UPROPERTY(EditAnywhere)
	float TimeBetweenChecks = 5.f;

private:
	FTimerHandle SpawnHandle;
};
