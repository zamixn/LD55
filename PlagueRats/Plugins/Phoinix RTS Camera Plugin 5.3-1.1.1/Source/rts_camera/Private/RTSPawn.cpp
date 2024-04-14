// © Phoenix-100

#include "RTSPawn.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/GameViewportClient.h"
#include "UnrealClient.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ARTSPawn::ARTSPawn()
{
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	SetRootComponent(SphereComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-60, 0, 0));
	SpringArm->TargetArmLength = 4000;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 6;
	SpringArm->CameraRotationLagSpeed = 6;
	SpringArm->bDoCollisionTest = false;
	CameraComponent->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ARTSPawn::BeginPlay()
{
	Super::BeginPlay();

	TargetZoom = SpringArm->TargetArmLength;
	TargetVector = GetActorLocation();
	FTimerHandle Handler;
	// Wait to make sure the viewport is initialized
	GetWorldTimerManager().SetTimer(Handler, this, &ARTSPawn::SetBoundaries, 0.1f, false, 0.2f);

	GEngine->GameViewport->Viewport->ViewportResizedEvent.AddUObject(this, &ARTSPawn::ViewportSizeChanged);
	
	DefaultArmLength = SpringArm->TargetArmLength;
	TargetRotation = DefaultRotation;

}

// Called every frame
void ARTSPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MouseMovement(DeltaTime);

	MoveTo(DeltaTime);
	if (HeightAdjustment)
	{
		SetTargetHeight();
		AdjustHeight(DeltaTime);
	}

	if (GetActorRotation().Yaw != TargetRotation)
	{
		const FRotator CurrentTargetRotation = UKismetMathLibrary::RInterpTo(GetActorRotation(),
																			 FRotator(GetActorRotation().Pitch,
																					  TargetRotation,
																					  GetActorRotation().Roll),
																			 DeltaTime,
																			 RotationSmoothness);

		SetActorRotation(CurrentTargetRotation, ETeleportType::None);
	}

	if (SpringArm->TargetArmLength != TargetZoom)
	{
		float CurrentTargetZoom = UKismetMathLibrary::FInterpTo(SpringArm->TargetArmLength,
																TargetZoom, DeltaTime,
																ZoomSmoothness);
		CurrentTargetZoom = UKismetMathLibrary::Clamp(CurrentTargetZoom, MinSpringArm, MaxSpringArm);
		SpringArm->TargetArmLength = CurrentTargetZoom;
	}
}

// Called to bind functionality to input
void ARTSPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the EnhancedInputComponent
	PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// Bind the actions
	PEI->BindAction(XAxisAction, ETriggerEvent::Triggered, this, &ARTSPawn::XMovement);
	XBinding = &PEI->BindActionValue(XAxisAction);

	PEI->BindAction(YAxisAction, ETriggerEvent::Triggered, this, &ARTSPawn::YMovement);
	YBinding = &PEI->BindActionValue(YAxisAction);

	PEI->BindAction(RotationAxisAction, ETriggerEvent::Triggered, this, &ARTSPawn::RotateCamera);
	PEI->BindAction(ZoomAxisAction, ETriggerEvent::Triggered, this, &ARTSPawn::Zoom);
	PEI->BindAction(ResetCameraAction, ETriggerEvent::Triggered, this, &ARTSPawn::ResetCamera);
	PEI->BindAction(SpawnRatAction, ETriggerEvent::Started, this, &ARTSPawn::SpawnRat);
}

// Called when the game starts or when spawned
void ARTSPawn::ResetCamera()
{
	TargetRotation = DefaultRotation;
	TargetZoom=DefaultArmLength;
}

void ARTSPawn::SpawnRat()
{
	BP_SpawnRat();
}

bool ARTSPawn::CanMoveInDirection(const FVector Direction) const
{
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;

	FVector TraceStart = TargetVector;
	FVector TraceEnd = TraceStart + Direction;

	// You can use FCollisionQueryParams to further configure the query
	// Here we add ourselves to the ignored list so we won't block the trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
	// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, MovementBlockingTraceChannel, QueryParams);

	// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
	UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());

	// If the trace hit something, bBlockingHit will be true,
	// and its fields will be filled with detailed info about what was hit
	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		UE_LOG(LogTemp, Log, TEXT("Trace hit actor"));
		return false;
	}
	else {
		return true;
	}
}

void ARTSPawn::XMovement(const FInputActionValue &Value)
{
	const float AxisValue = Value.GetMagnitude();
	const float MovMultiplier = MovementByZoomMultiplier * TargetZoom + MovementMultiplier;
	FVector Movement;
	Movement.X = AxisValue * MovMultiplier * GetAdjustedDeltaTime();
	Movement.Y = 0;
	Movement.Z = 0;
	Movement = UKismetMathLibrary::TransformDirection(GetActorTransform(), Movement);

	if (CanMoveInDirection(Movement))
	{
		TargetVector.X = TargetVector.X + Movement.X;
		TargetVector.Y = TargetVector.Y + Movement.Y;
	}
}

void ARTSPawn::YMovement(const FInputActionValue &Value)
{
	const float AxisValue = Value.GetMagnitude();
	const float MovMultiplier = MovementByZoomMultiplier * TargetZoom + MovementMultiplier;
	FVector Movement;
	Movement.X = 0;
	Movement.Y = AxisValue * MovMultiplier * GetAdjustedDeltaTime();
	Movement.Z = 0;
	Movement = UKismetMathLibrary::TransformDirection(GetActorTransform(), Movement);


	if (CanMoveInDirection(Movement))
	{
		TargetVector.X = TargetVector.X + Movement.X;
		TargetVector.Y = TargetVector.Y + Movement.Y;
	}
}

void ARTSPawn::MouseMovement(const float DeltaTime)
{
	const float XValue = XBinding->GetValue().Get<float>();
	const float YValue = YBinding->GetValue().Get<float>();
	const float MovMultiplier = MovementByZoomMultiplier * TargetZoom + MovementMultiplier;

	if (XValue != 0 || YValue != 0)
	{
		return;
	}

	float DirectionX = 0;
	float DirectionY = 0;

	FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	MousePosition = MousePosition * UWidgetLayoutLibrary::GetViewportScale(GetWorld());
	if (this->IsValidMousePosition(MousePosition, Top))
	{
		DirectionX = 1;
	}
	else if (IsValidMousePosition(MousePosition, Bottom))
	{
		DirectionX = -1;
	}

	if (IsValidMousePosition(FVector2D(MousePosition.Y, MousePosition.X), Right))
	{
		DirectionY = 1;
	}
	else if (IsValidMousePosition(FVector2D(MousePosition.Y, MousePosition.X), Left))
	{
		DirectionY = -1;
	}

	FVector Movement;
	Movement.X = DirectionX * MovMultiplier * GetAdjustedDeltaTime();
	Movement.Y = DirectionY * MovMultiplier * GetAdjustedDeltaTime();
	Movement.Z = 0;
	Movement = UKismetMathLibrary::TransformDirection(GetActorTransform(), Movement);
	TargetVector.X = TargetVector.X + Movement.X;
	TargetVector.Y = TargetVector.Y + Movement.Y;
}

void ARTSPawn::MoveTo(const float DeltaTime)
{
	const FVector CurrentTargetVector = UKismetMathLibrary::VInterpTo(GetActorLocation(), TargetVector, DeltaTime,
																	  MovementSmoothness);
	SetActorLocation(FVector(CurrentTargetVector.X, CurrentTargetVector.Y, GetActorLocation().Z));
}

void ARTSPawn::AdjustHeight(float DeltaTime)
{
	const FVector CurrentLocation = GetActorLocation();

	if (CurrentLocation.Z != TargetHeight)
	{
		const float HeightToSet = UKismetMathLibrary::FInterpTo(CurrentLocation.Z, TargetHeight,
																DeltaTime,
																HeightAdjustmentSmoothness);
		SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y, HeightToSet));
	}
}

void ARTSPawn::RotateCamera(const FInputActionValue &Value)
{
	float AxisValue = Value.GetMagnitude();
	int ZoomStep = (MaxSpringArm - MinSpringArm) / ZoomSteps;

	TargetRotation = TargetRotation + (AxisValue * RotationMultiplier * GetAdjustedDeltaTime());
}

void ARTSPawn::Zoom(const FInputActionValue &Value)
{
	float AxisValue = Value.GetMagnitude();
	if (AxisValue != 0)
	{
		TargetZoom = TargetZoom + (AxisValue * ZoomMultiplier);

		if (UseZoomSteps)
		{
			int ZoomStepSize = (MaxSpringArm - MinSpringArm) / ZoomSteps;
			float ZoomStep = SpringArm->TargetArmLength / ZoomStepSize;
			int Step = UKismetMathLibrary::Round(ZoomStep);
			if (AxisValue > 0)
			{
				Step++;
			}
			else if (AxisValue < 0)
			{
				Step--;
			}
			TargetZoom = Step * ZoomStepSize;
		}

		TargetZoom = UKismetMathLibrary::Clamp(TargetZoom, MinSpringArm, MaxSpringArm);
	}
}

bool ARTSPawn::IsValidMousePosition(const FVector2D Positions, const FVector4 Rules)
{
	const bool InputY = Positions.Y >= Rules.X && Positions.Y <= Rules.Y;
	const bool InputX = Positions.X >= Rules.Z && Positions.X <= Rules.W;
	return InputX && InputY;
}

void ARTSPawn::SetBoundaries()
{
	const FVector2D Result = UWidgetLayoutLibrary::GetViewportSize(GetWorld());

	Top = FVector4(0, 0, 0, 0);
	Bottom = FVector4(0, 0, 0, 0);
	Left = FVector4(0, 0, 0, 0);
	Right = FVector4(0, 0, 0, 0);

	Top.Y = (MovementZoneInPercent / 100.f) * Result.Y;
	Top.W = Result.X;

	Bottom.X = (1 - (MovementZoneInPercent / 100.f)) * Result.Y;
	Bottom.Y = Result.Y;
	Bottom.W = Result.X;

	Left.Y = (MovementZoneInPercent / 100.f) * Result.X;
	Left.W = Result.Y;

	Right.X = (1 - (MovementZoneInPercent / 100.f)) * Result.X;
	Right.Y = Result.X;
	Right.W = Result.Y;

	StartHeight = GetActorLocation().Z;
	PreviousHeight = GetActorLocation().Z;

	if (IgnoreBoundaries)
	{
		Top.X = -Deactivate;
		Top.Z = -Deactivate;
		Top.W = Deactivate;

		Bottom.Y = Deactivate;
		Bottom.Z = -Deactivate;
		Bottom.W = Deactivate;

		Left.X = -Deactivate;
		Left.Z = -Deactivate;
		Left.W = Deactivate;

		Right.Y = Deactivate;
		Right.Z = -Deactivate;
		Right.W = Deactivate;
	}
}

void ARTSPawn::SetTargetHeight()
{
	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = GetActorLocation();

	if (TranceFromCamera)
	{
		Start = CameraComponent->GetComponentLocation();
		End = CameraComponent->GetComponentLocation();
	}

	Start.Z = 999999;
	End.Z = -999999;

	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(TraceChannel);
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, TraceChannel);

	if (UKismetMathLibrary::Abs(PreviousHeight - HitResult.Location.Z) >= Threshold)
	{
		TargetHeight = HitResult.Location.Z;
		PreviousHeight = HitResult.Location.Z;
	}
	else if (UKismetMathLibrary::Abs(HitResult.Location.Z - StartHeight) < Threshold)
	{
		TargetHeight = StartHeight;
	}
}

float ARTSPawn::GetAdjustedDeltaTime() const
{
	return GetWorld()->GetDeltaSeconds() * 100;
}

void ARTSPawn::ViewportSizeChanged(FViewport *ViewPort, uint32 val)
{
	SetBoundaries();
}
