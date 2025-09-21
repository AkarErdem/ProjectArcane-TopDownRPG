// Copyright (c) 2025 Erdem Akar

#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/ArcaneAbilitySystemComponent.h"
#include "AbilitySystem/ArcaneAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const UArcaneAttributeSet* ArcaneAttributeSet = CastChecked<UArcaneAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(ArcaneAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(ArcaneAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(ArcaneAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(ArcaneAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const UArcaneAttributeSet* ArcaneAttributeSet = CastChecked<UArcaneAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ArcaneAttributeSet->GetHealthAttribute())
	                      .AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ArcaneAttributeSet->GetHealthAttribute())
	                      .AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ArcaneAttributeSet->GetMaxHealthAttribute())
	                      .AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ArcaneAttributeSet->GetManaAttribute())
	                      .AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ArcaneAttributeSet->GetMaxManaAttribute())
	                      .AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

	CastChecked<UArcaneAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda([this](const FGameplayTagContainer& AssetTags)
	{
		for(const FGameplayTag& Tag : AssetTags)
		{
			if(Tag.MatchesTag(MessagesTag))
			{
				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				OnWidgetMessageReceived.Broadcast(*Row);
			}
		}
	});
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
