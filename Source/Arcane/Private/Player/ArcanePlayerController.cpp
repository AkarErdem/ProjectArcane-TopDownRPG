// Copyright (c) 2025 Erdem Akar


#include "Player/ArcanePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/HighlightInterface.h"

AArcanePlayerController::AArcanePlayerController()
{
	bReplicates = true;
}

void AArcanePlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(ArcaneInputMappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(ArcaneInputMappingContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AArcanePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,  &AArcanePlayerController::Move);
}

void AArcanePlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AArcanePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AArcanePlayerController::CursorTrace()
{
	// Unhighlight
	auto ClearHighlight = [this]
	{
		if (HighlightedInterface)
		{
			HighlightedInterface->UnHighlightActor();
			UE_LOG(LogTemp, Display, TEXT("%s clear"), *HighlightedInterface.GetObject()->GetName());
		}
		this->HighlightedInterface = nullptr;
	};

	// Highlight
	auto Highlight = [this](const TScriptInterface<IHighlightInterface>& HighlightInterface)
	{
		HighlightInterface->HighlightActor();
		this->HighlightedInterface = HighlightInterface;

		UE_LOG(LogTemp, Display, TEXT("%s highlighted"), *HighlightInterface.GetObject()->GetName());
	};

	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, /*bTraceComplex*/ false, CursorHit);
	if (!CursorHit.bBlockingHit)
	{
		ClearHighlight();
		return;
	}

	AActor* HighlightedActor = CursorHit.GetActor();
	if (IHighlightInterface* HighlightedPtr = Cast<IHighlightInterface>(HighlightedActor))
	{
		if (HighlightedInterface && HighlightedActor == HighlightedInterface.GetObject())
		{
			return;
		}
		ClearHighlight();
		TScriptInterface<IHighlightInterface> HighlightedInterfacePtr;
		HighlightedInterfacePtr.SetObject(HighlightedActor);
		HighlightedInterfacePtr.SetInterface(HighlightedPtr);
		Highlight(HighlightedInterfacePtr);
	}
	else
	{
		ClearHighlight();
	}
}
