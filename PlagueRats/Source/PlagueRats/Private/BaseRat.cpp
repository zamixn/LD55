// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRat.h"

#include "BaseVillager.h"
#include "NiagaraComponent.h"
#include "RatPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/AIModule/Classes/AIController.h"

// Sets default values
ABaseRat::ABaseRat()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DeathParticles = CreateDefaultSubobject<UNiagaraComponent>(TEXT("DeathParticles"));
	DeathParticles->SetupAttachment(GetCapsuleComponent());
	DeathParticles->SetAutoActivate(false);

	SpawnParticles = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SpawnParticles"));
	SpawnParticles->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void ABaseRat::BeginPlay()
{
	Super::BeginPlay();

	AttackVillager();
	GetWorldTimerManager().SetTimer(TryAttackingVillagerHandle, this, &ABaseRat::TryAttackingVillager, TimeUntilNextAttackTry);
	ApplyStats();

	const float Lifetime = FMath::RandRange(MinAliveTime, MaxAliveTime) + GetAdditionalLifetime();
	GetWorldTimerManager().SetTimer(DeathHandle, this, &ABaseRat::Die, Lifetime);
}

void ABaseRat::SetRatBigScale() const
{
	if(USkeletalMeshComponent* MeshComponent = GetMesh())
	{
		MeshComponent->SetWorldScale3D(BigScaleToSet);
	}
}

void ABaseRat::SetRatSmallScale() const
{
	if(USkeletalMeshComponent* MeshComponent = GetMesh())
	{
		MeshComponent->SetWorldScale3D(SmallScaleToSet);
	}
}

void ABaseRat::TryAttackingVillager()
{
	if(!CurrentTarget)
	{
		AttackVillager();
	}
}

void ABaseRat::OnMoveComplete(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if(Result == EPathFollowingResult::Success)
	{
		if(!bIsDead)
		{
			SetRatSmallScale();
			if(USkeletalMeshComponent* MeshComponent = GetMesh())
			{
				MeshComponent->PlayAnimation(nullptr, true);
				if(CurrentTarget)
				{
					AttackedVillagers.Add(CurrentTarget);
					CurrentTarget->IncreasePlagueCounter();

					if(ARatPlayerController* PlayerController = Cast<ARatPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
					{
						PlayerController->OnRatAttackedVillager(CurrentTarget->IsDead());
						const float TimeUntilNextAttack = FMath::RandRange(MinTimeToWaitBeforeNextAttack, MaxTimeToWaitBeforeNextAttack);
						GetWorldTimerManager().SetTimer(AttackHandle, this, &ABaseRat::AttackVillager, TimeUntilNextAttack);
					}
				}
			}
		}
	}
	else
	{
		AttackVillager();
	}
}

void ABaseRat::AttackVillager()
{
	if(ABaseVillager* ClosestVillager = GetClosestVillager())
	{
		CurrentTarget = ClosestVillager;
		if(AAIController* AiController = GetController<AAIController>())
		{
			AiController->ReceiveMoveCompleted.AddUniqueDynamic(this, &ABaseRat::OnMoveComplete);
			AiController->MoveToActor(CurrentTarget, 5.f, false);
			if(USkeletalMeshComponent* MeshComponent = GetMesh())
			{
				MeshComponent->PlayAnimation(MeshAnimation, true);
			}

			GetWorldTimerManager().SetTimerForNextTick(this, &ABaseRat::SetRatBigScale);
		}
	}
	else
	{
		CurrentTarget = nullptr;
	}
}

ABaseVillager* ABaseRat::GetClosestVillager() const
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, ABaseVillager::StaticClass(), OutActors);

	TArray<ABaseVillager*> ViableVillagers;
	for(AActor* Actor : OutActors)
	{
		if(ABaseVillager* Villager = Cast<ABaseVillager>(Actor))
		{
			if(!Villager->IsDead() && !AttackedVillagers.Contains(Villager))
			{
				ViableVillagers.Add(Villager);
			}
		}
	}

	if(!ViableVillagers.IsEmpty())
	{
		ABaseVillager* ClosestVillager = ViableVillagers[0];
		for(int32 i = 1; i < ViableVillagers.Num(); ++i)
		{
			if(ViableVillagers[i]->GetDistanceTo(this) < ClosestVillager->GetDistanceTo(this))
			{
				ClosestVillager = ViableVillagers[i];
			}
		}
		return ClosestVillager;
	}

	return nullptr;
}

void ABaseRat::ApplyStats() const
{
	if(UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement())
	{
		CharacterMovementComponent->MaxWalkSpeed += MovementSpeedMultiplier * GetAdditionalMoveSpeed();
	}
}

float ABaseRat::GetAdditionalMoveSpeed() const
{
	if(const ARatPlayerController* PlayerController = Cast<ARatPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		return PlayerController->RatSpeed;
	}

	return 0.f;
}

float ABaseRat::GetAdditionalLifetime() const
{
	if(const ARatPlayerController* PlayerController = Cast<ARatPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		return PlayerController->RatLifetime;
	}
	
	return 0.f;
}

void ABaseRat::Die()
{
	if(!bIsDead)
	{
		bIsDead = true;
		if(UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement())
		{
			CharacterMovementComponent->StopMovementImmediately();
		}

		DeathParticles->Activate(true);
		if(USkeletalMeshComponent* RatMesh = GetMesh())
		{
			RatMesh->SetHiddenInGame(true, false);
		}
		GetWorldTimerManager().ClearTimer(TryAttackingVillagerHandle);

		if(const ARatPlayerController* PlayerController = Cast<ARatPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
		{
			
		}
	}
}

