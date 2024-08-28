// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlagueDoctor.h"

#include "BaseRat.h"
#include "BaseVillagerSpawner.h"
#include "NiagaraComponent.h"
#include "PlagueDoctorCharges.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ABasePlagueDoctor::ABasePlagueDoctor()
{
	ChargesLeft = CreateDefaultSubobject<UWidgetComponent>(TEXT("ChargesLeft"));
	ChargesLeft->SetupAttachment(GetRootComponent());
	ChargesLeft->SetWidgetSpace(EWidgetSpace::Screen);

	DamageSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DamageSphere"));
	DamageSphere->SetupAttachment(GetRootComponent());
	DamageSphere->SetGenerateOverlapEvents(true);
	DamageSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	DamageSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABasePlagueDoctor::OnDamageSphereOverlap);

	DamageParticles = CreateDefaultSubobject<UNiagaraComponent>(TEXT("DamageParticles"));
	DamageParticles->SetupAttachment(GetRootComponent());
	DamageParticles->SetAutoActivate(true);
}

void ABasePlagueDoctor::OnDamageSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bIsDead)
	{
		return;
	}

	if(ABaseRat* BaseRat = Cast<ABaseRat>(OtherActor))
	{
		BaseRat->Die();
		
		--NumberOfChargesLeft;
		if(const UPlagueDoctorCharges* PlagueDoctorCharges = Cast<UPlagueDoctorCharges>(ChargesLeft->GetWidget()))
		{
			PlagueDoctorCharges->UpdateCharges(NumberOfChargesLeft);
		}

		if(NumberOfChargesLeft <= 0 && !bIsDead)
		{
			bIsDead = true;
			Die();
		}
	}
}

void ABasePlagueDoctor::BeginPlay()
{
	Super::BeginPlay();

	if(const UPlagueDoctorCharges* PlagueDoctorCharges = Cast<UPlagueDoctorCharges>(ChargesLeft->GetWidget()))
	{
		PlagueDoctorCharges->UpdateCharges(NumberOfChargesLeft);
	}
}

void ABasePlagueDoctor::Die()
{
	if(!DeathNoises.IsEmpty())
	{
		const int32 RandomIndex = FMath::RandRange(0, DeathNoises.Num() - 1);
		UGameplayStatics::PlaySoundAtLocation(this, DeathNoises[RandomIndex], GetActorLocation());
	}

	DamageParticles->Deactivate();
	ChargesLeft->SetHiddenInGame(true, true);

	if(UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement())
	{
		CharacterMovementComponent->StopMovementImmediately();
	}

	CleanUpAfterDeath();

	if(USkeletalMeshComponent* DoctorMesh = GetMesh())
	{
		DoctorMesh->SetAllBodiesSimulatePhysics(true);
		DoctorMesh->SetSimulatePhysics(true);
		DoctorMesh->WakeAllRigidBodies();
	}

	if(UCapsuleComponent* DoctorCapsuleComponent = GetCapsuleComponent())
	{
		DoctorCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DoctorCapsuleComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
}

void ABasePlagueDoctor::CleanUpAfterDeath()
{
	if(Spawner)
	{
		Spawner->DecrementCurrentAmountOfVillagers();
	}

	GetWorldTimerManager().SetTimer(DestroyEnemyHandle, this, &ABaseEnemy::DestroyEnemy, TimeUntilDestroy);
}
