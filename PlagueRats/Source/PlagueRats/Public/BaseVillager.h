// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseVillager.generated.h"

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE bool IsDead() const { return bIsDead; }

private:
	bool bIsDead = false;
};
