// Copyright (c) 2025 Erdem Akar

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/ArcaneAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfo);

	for(auto& Info : AttributeInfo->AttributeInformation)
	{
		BroadcastAttributeInfo(Info.AttributeTag);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfo);

	for(auto& Info : AttributeInfo->AttributeInformation)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Info.AttributeGetter)
		                      .AddLambda([this, Info](const FOnAttributeChangeData&)
		                      {
			                      BroadcastAttributeInfo(Info.AttributeTag);
		                      });
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& Tag) const
{
	FArcaneAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Tag);
	Info.AttributeValue = Info.AttributeGetter.GetNumericValue(AttributeSet);
	AttributeInfoChanged.Broadcast(Info);
}
