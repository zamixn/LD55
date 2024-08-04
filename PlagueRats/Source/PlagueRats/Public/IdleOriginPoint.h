// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IdleOriginPoint.generated.h"

class USphereComponent;

UCLASS()
class PLAGUERATS_API AIdleOriginPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIdleOriginPoint();
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> Sphere = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
