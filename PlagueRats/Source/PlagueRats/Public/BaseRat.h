// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AITypes.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "BaseRat.generated.h"

class ABaseVillager;

UCLASS()
class PLAGUERATS_API ABaseRat : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseRat();

	UFUNCTION()
	void OnMoveComplete(FAIRequestID RequestID, EPathFollowingResult::Type Result);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetRatBigScale() const;
	void SetRatSmallScale() const;

	UPROPERTY(EditAnywhere)
	FVector BigScaleToSet = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	FVector SmallScaleToSet = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimationAsset> MeshAnimation = nullptr;
	
	TObjectPtr<ABaseVillager> CurrentTarget = nullptr;

private:
	void AttackVillager();
	ABaseVillager* GetClosestVillager() const;
	TSet<ABaseVillager*> AttackedVillagers;
	bool bIsDead = false;
};
