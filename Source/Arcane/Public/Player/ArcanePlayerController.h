// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArcanePlayerController.generated.h"

class USplineComponent;
class UArcaneAbilitySystemComponent;
class UArcaneInputConfig;
class IHighlightInterface;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FGameplayTag;

UCLASS()
class ARCANE_API AArcanePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AArcanePlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override
	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& InputActionValue);
	void CursorTrace();

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	void AutoRun();

	UArcaneAbilitySystemComponent* GetASC();

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> ArcaneInputMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UArcaneInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UArcaneAbilitySystemComponent> ArcaneAbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	float ShortPressThreshold = 0.5f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> PathSpline;

	TScriptInterface<IHighlightInterface> HighlightedInterface;
	FHitResult CursorHit;

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	bool bAutoRunning = false;
	bool bIsTargeting = false;
};
