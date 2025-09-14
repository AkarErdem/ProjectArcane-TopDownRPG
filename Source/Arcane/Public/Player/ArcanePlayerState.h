// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/ArcaneAttributeSet.h"
#include "GameFramework/PlayerState.h"
#include "ArcanePlayerState.generated.h"

class UArcaneAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class ARCANE_API AArcanePlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AArcanePlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	UPROPERTY()
	TObjectPtr<UArcaneAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UArcaneAttributeSet> AttributeSet;
};
