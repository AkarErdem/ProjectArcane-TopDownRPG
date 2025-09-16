// Copyright (c) 2025 Erdem Akar

#include "UI/WidgetController/ArcaneWidgetController.h"

void UArcaneWidgetController::SetWidgetControllerData(const FWidgetControllerData& WidgetControllerData)
{
	PlayerController = WidgetControllerData.PlayerController;
	PlayerState = WidgetControllerData.PlayerState;
	AbilitySystemComponent = WidgetControllerData.AbilitySystemComponent;
	AttributeSet = WidgetControllerData.AttributeSet;
}

void UArcaneWidgetController::BroadcastInitialValues()
{
}

void UArcaneWidgetController::BindCallbacksToDependencies()
{
}
