// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "BaseHUD.h"
#include "BaseRat.h"
#include "PauseMenu.h"
#include "RatPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundCue.h"
#include "PlagueStaticFunctions.h"

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &APlayerPawn::PauseGame);
		EnhancedInputComponent->BindAction(SpawnRatAction, ETriggerEvent::Started, this, &APlayerPawn::SpawnRat);
	}
}

void APlayerPawn::PauseGame()
{
	if(const APlayerController* PlayerController = GetController<APlayerController>())
	{
		if(const ABaseHUD* PlayerHUD = PlayerController->GetHUD<ABaseHUD>())
		{
			if(PlayerHUD->PauseMenu)
			{
				PlayerHUD->PauseMenu->Show(false);
			}
		}
	}
}

void APlayerPawn::SpawnRat()
{
	if(ARatPlayerController* RatPlayerController = GetController<ARatPlayerController>())
	{
		if(RatPlayerController->CanSpawnRat())
		{
			for(int32 i = 1; i <= RatPlayerController->RatCount; ++i)
			{
				FVector WorldLocation = FVector::ZeroVector;
				FVector WorldDirection = FVector::ZeroVector;
				RatPlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

				const FVector TraceEnd = WorldLocation + WorldDirection * WorldDirectionScale;
				FHitResult HitResult;
				UKismetSystemLibrary::LineTraceSingle(this, WorldLocation, TraceEnd, TraceTypeQuery1, false, TArray<AActor*>(), EDrawDebugTrace::None, HitResult, true);

				if(UWorld* World = GetWorld())
				{
					FRatData ratData;
					PlagueStaticFunctions::GetGameMode(this)->RatDataAsset->GetRatOfType(RatPlayerController->CurrentRatType, ratData);
					TSubclassOf<ABaseRat> RatToSpawn = ratData.ClassToSpawn;
					
					if(const AActor* SpawnedRat = World->SpawnActor(RatToSpawn, &HitResult.Location))
					{
						SpawnLocation = SpawnedRat->GetActorLocation();
					}
				}
			}

			if(!SpawnNoises.IsEmpty())
			{
				const int32 RandomIndex = FMath::RandRange(0, SpawnNoises.Num() - 1);
				UGameplayStatics::PlaySoundAtLocation(this, SpawnNoises[RandomIndex], SpawnLocation);
			}

			RatPlayerController->OnRatsSpawned();
		}
	}
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}
