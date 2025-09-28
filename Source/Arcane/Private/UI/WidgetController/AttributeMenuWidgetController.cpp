// Copyright (c) 2025 Erdem Akar

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/ArcaneAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Game/ArcaneGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	check(AttributeInfo);

	const UArcaneAttributeSet* ArcaneAttributeSet = CastChecked<UArcaneAttributeSet>(AttributeSet);

	FArcaneAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(ArcaneGameplayTags::Attributes_Primary_Strength);
	Info.AttributeValue = ArcaneAttributeSet->GetIntelligence();
	AttributeInfoChanged.Broadcast(Info);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
}
