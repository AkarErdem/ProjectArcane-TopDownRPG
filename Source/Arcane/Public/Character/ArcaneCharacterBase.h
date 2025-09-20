// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/ArcaneAttributeSet.h"
#include "GameFramework/Character.h"
#include "ArcaneCharacterBase.generated.h"

class UArcaneAttributeSet;
class UAttributeSet;
class UArcaneAbilitySystemComponent;

UCLASS(Abstract)
class ARCANE_API AArcaneCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AArcaneCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	FORCEINLINE UAttributeSet* GetAttributeSet() const
	{
		return AttributeSet;
	}

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UArcaneAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UArcaneAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();
};
