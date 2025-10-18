// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Character/ArcaneCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "ArcaneEnemy.generated.h"

class UWidgetComponent;

UCLASS()
class ARCANE_API AArcaneEnemy : public AArcaneCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AArcaneEnemy();

	//~ Begin IHighlight Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted;
	//~ End IHighlight Interface

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnMaxHealthChanged;

protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ End AActor Interface

	//~ Begin ICombat Interface
	FORCEINLINE virtual int32 GetCharacterLevel() override
	{
		return Level;
	}

	//~ End ICombat Interface

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Defaults")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

private:
	FDelegateHandle HealthChangedHandle;
	FDelegateHandle MaxHealthChangedHandle;

	void Initialize();
	void Cleanup();
};
