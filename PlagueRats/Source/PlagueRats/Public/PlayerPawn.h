// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSPawn.h"
#include "RTSPawn.h"
#include "PlayerPawn.generated.h"

class ABaseRat;
class UInputAction;

/**
 * 
 */
UCLASS()
class PLAGUERATS_API APlayerPawn : public ARTSPawn
{
	GENERATED_BODY()

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void PauseGame();
	
	UFUNCTION(BlueprintCallable, Category = "RTS Camera")
	void SpawnRat();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputAction> PauseAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TObjectPtr<UInputAction> SpawnRatAction = nullptr;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<USoundCue*> SpawnNoises;
	
	UPROPERTY(EditAnywhere)
	float WorldDirectionScale = 10000.f;

private:
	FVector SpawnLocation = FVector::ZeroVector;
};
