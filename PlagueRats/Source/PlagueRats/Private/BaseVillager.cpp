// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVillager.h"

#include "AIController.h"
#include "BaseVillagerSpawner.h"
#include "IdleOriginPoint.h"
#include "NavigationSystem.h"
#include "PlagueBar.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY(LogVillager);

// Sets default values
ABaseVillager::ABaseVillager()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpeechBubble = CreateDefaultSubobject<UWidgetComponent>(TEXT("SpeechBubble"));
	SpeechBubble->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	PlagueCounter = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlagueCounter"));
	PlagueCounter->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ABaseVillager::BeginPlay()
{
	Super::BeginPlay();

	SetRandomSkin();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, AIdleOriginPoint::StaticClass(), OutActors);
	if(!OutActors.IsEmpty())
	{
		const int32 RandomIndex = FMath::RandRange(0, OutActors.Num() - 1);
		if(const AIdleOriginPoint* IdleOriginPoint = Cast<AIdleOriginPoint>(OutActors[RandomIndex]))
		{
			if(IdleOriginPoint->Sphere)
			{
				RoamOriginPoint = IdleOriginPoint->GetActorLocation();
				RoamRadius = IdleOriginPoint->Sphere->GetUnscaledSphereRadius();
				Roam();
			}
		}
	}
	else
	{
		UE_LOG(LogVillager, Warning, TEXT("### No origin point set for AI to target"));
	}
}

void ABaseVillager::IncreasePlagueCounter()
{
	++LevelOfInfection;
	if(UPlagueBar* PlagueBar = Cast<UPlagueBar>(PlagueCounter->GetWidget()))
	{
		PlagueBar->ChangePlagueVisuals(LevelOfInfection);
	}

	if(LevelOfInfection >= 3)
	{
		Die();
	}
}

void ABaseVillager::OnMoveComplete(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if(USkeletalMeshComponent* VillagerMesh = GetMesh())
	{
		VillagerMesh->PlayAnimation(IdleAnimation, true);
	}

	const float IdleTime = FMath::RandRange(MinWaitTime, MaxWaitTime);
	GetWorldTimerManager().SetTimer(IdleHandle, this, &ABaseVillager::Roam, IdleTime);
}

void ABaseVillager::Die()
{
	bIsDead = true;
	if(!DeathNoises.IsEmpty())
	{
		const int32 RandomIndex = FMath::RandRange(0, DeathNoises.Num() - 1);
		UGameplayStatics::PlaySoundAtLocation(this, DeathNoises[RandomIndex], GetActorLocation());
	}
	SpeechBubble->SetHiddenInGame(false, true);
	
	if(UUserWidget* Widget = PlagueCounter->GetWidget())
	{
		Widget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if(UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->StopMovementImmediately();
	}

	CleanupAfterDeath();

	if(USkeletalMeshComponent* CharMesh = GetMesh())
	{
		CharMesh->SetAllBodiesSimulatePhysics(true);
		CharMesh->SetSimulatePhysics(true);
		CharMesh->WakeAllRigidBodies();
	}

	if(UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Capsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
}

void ABaseVillager::HideVillager()
{
	SpeechBubble->SetHiddenInGame(true, true);
	GetWorldTimerManager().SetTimer(DestroyEnemyHandle, this, &ABaseEnemy::DestroyEnemy, TimeUntilDestroy);
}

void ABaseVillager::CleanupAfterDeath()
{
	if(Spawner)
	{
		Spawner->DecrementCurrentAmountOfVillagers();
	}

	GetWorldTimerManager().SetTimer(HideVillagerHandle, this, &ABaseVillager::HideVillager, TimeUntilHide);
}

void ABaseVillager::SetRandomSkin()
{
	if(!Skins.IsEmpty())
	{
		if(USkeletalMeshComponent* VillagerMesh = GetMesh())
		{
			const int32 RandomIndex = FMath::RandRange(0, Skins.Num() - 1);
			VillagerMesh->SetMaterial(0, Skins[RandomIndex]);
		}
	}
}

void ABaseVillager::Roam()
{
	if(bIsDead)
	{
		return;
	}
	
	if(USkeletalMeshComponent* VillagerMesh = GetMesh())
	{
		VillagerMesh->PlayAnimation(WalkAnimation, true);
	}

	if(const UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetNavigationSystem(this))
	{
		if(AAIController* AiController = GetController<AAIController>())
		{
			FNavLocation RandomLocation;
			NavigationSystem->GetRandomReachablePointInRadius(RoamOriginPoint, RoamRadius, RandomLocation);
			AiController->ReceiveMoveCompleted.AddUniqueDynamic(this, &ABaseVillager::OnMoveComplete);
			AiController->MoveToLocation(RandomLocation, RoamAcceptanceRadius, false);
		}
	}
}

