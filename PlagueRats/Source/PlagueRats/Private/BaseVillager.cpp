// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVillager.h"

#include "BaseVillagerSpawner.h"
#include "PlagueBar.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ABaseVillager::ABaseVillager()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpeechBubble = CreateDefaultSubobject<UWidgetComponent>(TEXT("SpeechBubble"));
	SpeechBubble->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ABaseVillager::BeginPlay()
{
	Super::BeginPlay();
	
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

	if(USkeletalMeshComponent* Mesh = GetMesh())
	{
		Mesh->SetAllBodiesSimulatePhysics(true);
		Mesh->SetSimulatePhysics(true);
		Mesh->WakeAllRigidBodies();
	}

	if(UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Capsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
}

void ABaseVillager::DestroyVillager()
{
	Destroy();
}

void ABaseVillager::HideVillager()
{
	SpeechBubble->SetHiddenInGame(true, true);
	GetWorldTimerManager().SetTimer(DestroyVillagerHandle, this, &ABaseVillager::DestroyVillager, TimeUntilDestroy);
}

void ABaseVillager::CleanupAfterDeath()
{
	if(Spawner)
	{
		Spawner->DecrementCurrentAmountOfVillagers();
	}

	GetWorldTimerManager().SetTimer(HideVillagerHandle, this, &ABaseVillager::HideVillager, TimeUntilHide);
}

