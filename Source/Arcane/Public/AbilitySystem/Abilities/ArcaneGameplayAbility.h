// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ArcaneGameplayAbility.generated.h"

UCLASS()
class ARCANE_API UArcaneGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

	virtual void NotifyAbilityTaskWaitingOnAvatar(UAbilityTask* AbilityTask) override;
};
