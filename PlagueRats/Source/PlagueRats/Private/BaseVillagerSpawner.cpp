// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVillagerSpawner.h"

#include "BaseEnemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABaseVillagerSpawner::ABaseVillagerSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));

	SpawnBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBounds"));
	SpawnBounds->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ABaseVillagerSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnHandle, this, &ABaseVillagerSpawner::AttemptToSpawnVillagers, TimeBetweenChecks, true);
}

void ABaseVillagerSpawner::AttemptToSpawnVillagers()
{
	if(CurrentAmountOfVillagers >= AmountToKeepAlive)
	{
		return;
	}

	if(UWorld* World = GetWorld())
	{
		FVector Origin = FVector::ZeroVector;
		FVector BoxExtent = FVector::ZeroVector;
		float SphereRadius = 0.f;
		UKismetSystemLibrary::GetComponentBounds(SpawnBounds, Origin, BoxExtent, SphereRadius);
		const float RandomX = FMath::RandRange(Origin.X - BoxExtent.X / 2.f, Origin.X + BoxExtent.X / 2.f);
		const float RandomY = FMath::RandRange(Origin.Y - BoxExtent.Y / 2.f, Origin.Y + BoxExtent.Y / 2.f);
		const FVector SpawnPoint(RandomX, RandomY, Origin.Z);
		const FRotator SpawnRotation(0.f, FMath::RandRange(-180.f, 180.f), 0.f);
		if(ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(World->SpawnActor(VillagerClass, &SpawnPoint, &SpawnRotation)))
		{
			BaseEnemy->Spawner = this;
			++CurrentAmountOfVillagers;
		}
	}
}

