// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArcanePlayerController.generated.h"

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
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> ArcaneInputMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY()
	TScriptInterface<IHighlightInterface> HighlightedInterface;

	void Move(const FInputActionValue& InputActionValue);
	void CursorTrace();

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UArcaneInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UArcaneAbilitySystemComponent> ArcaneAbilitySystemComponent;

	UArcaneAbilitySystemComponent* GetASC();

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
};
