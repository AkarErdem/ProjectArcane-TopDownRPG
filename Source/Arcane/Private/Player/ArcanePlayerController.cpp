// Copyright (c) 2025 Erdem Akar

#include "Player/ArcanePlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/ArcaneAbilitySystemComponent.h"
#include "Input/ArcaneInputComponent.h"
#include "Interaction/HighlightInterface.h"

AArcanePlayerController::AArcanePlayerController()
{
	bReplicates = true;
}

void AArcanePlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(ArcaneInputMappingContext);

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(ArcaneInputMappingContext, 0);
	}

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

	UArcaneInputComponent* ArcaneInputComponent = CastChecked<UArcaneInputComponent>(InputComponent);
	ArcaneInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AArcanePlayerController::Move);

	ArcaneInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AArcanePlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>())
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
		if(HighlightedInterface)
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
	if(!CursorHit.bBlockingHit)
	{
		ClearHighlight();
		return;
	}

	AActor* HighlightedActor = CursorHit.GetActor();
	if(IHighlightInterface* HighlightedPtr = Cast<IHighlightInterface>(HighlightedActor))
	{
		if(HighlightedInterface && HighlightedActor == HighlightedInterface.GetObject())
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

void AArcanePlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

void AArcanePlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if(GetASC() == nullptr)
	{
		return;
	}
	GetASC()->AbilityInputTagReleased(InputTag);
}

void AArcanePlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if(GetASC() == nullptr)
	{
		return;
	}
	GetASC()->AbilityInputTagHeld(InputTag);
}

UArcaneAbilitySystemComponent* AArcanePlayerController::GetASC()
{
	if(ArcaneAbilitySystemComponent == nullptr)
	{
		ArcaneAbilitySystemComponent = Cast<UArcaneAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return ArcaneAbilitySystemComponent;
}
