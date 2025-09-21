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

#define BIND_ATTRIBUTE(AttributeName, ArcaneAttributeSet) \
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ArcaneAttributeSet->Get##AttributeName##Attribute()) \
	.AddLambda([this](const FOnAttributeChangeData& Data) \
	{ \
	On##AttributeName##Changed.Broadcast(Data.NewValue); \
	});
	BIND_ATTRIBUTE(Health, ArcaneAttributeSet);
	BIND_ATTRIBUTE(MaxHealth, ArcaneAttributeSet);
	BIND_ATTRIBUTE(Mana, ArcaneAttributeSet);
	BIND_ATTRIBUTE(MaxMana, ArcaneAttributeSet);
#undef BIND_ATTRIBUTE

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
