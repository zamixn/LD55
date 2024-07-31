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

	void SetRatScale();

	UPROPERTY(EditAnywhere)
	FVector ScaleToSet = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimationAsset> MeshAnimation = nullptr;
	
	TObjectPtr<ABaseVillager> CurrentTarget = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void AttackVillager();
	ABaseVillager* GetClosestVillager() const;
	TSet<ABaseVillager*> AttackedVillagers;
};
