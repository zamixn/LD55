// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRat.h"

#include "BaseVillager.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/AIModule/Classes/AIController.h"

// Sets default values
ABaseRat::ABaseRat()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseRat::BeginPlay()
{
	Super::BeginPlay();

	AttackVillager();
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

