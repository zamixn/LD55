// Fill out your copyright notice in the Description page of Project Settings.


#include "IdleOriginPoint.h"

#include "Components/SphereComponent.h"

// Sets default values
AIdleOriginPoint::AIdleOriginPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
	Sphere->SetSphereRadius(2500.f);
}

// Called when the game starts or when spawned
void AIdleOriginPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

