// Copyright (c) 2025 Erdem Akar

#include "UI/HUD/ArcaneHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/ArcaneUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

#define INIT_WIDGET_CONTROLLER(Name) \
void AArcaneHUD::Init##Name(APlayerController* PlayerController, APlayerState* PlayerState, \
                             UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet) \
{ \
	checkf(Name##WidgetClass, TEXT("Name##WidgetClass uninitialized, fill out BP_ArcaneHUD.")); \
	checkf(Name##WidgetControllerClass, TEXT("Name##WidgetControllerClass uninitialized, fill out BP_ArcaneHUD.")); \
 \
	const auto Data = FWidgetControllerData(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet); \
	U##Name##WidgetController* WidgetController = Get##Name##WidgetController(Data); \
 \
	Name##Widget = CreateWidget<UArcaneUserWidget>(GetWorld(), Name##WidgetClass); \
	Name##Widget->SetWidgetController(WidgetController); \
	WidgetController->BroadcastInitialValues(); \
 \
	Name##Widget->AddToViewport(); \
}

INIT_WIDGET_CONTROLLER(Overlay);

#undef INIT_WIDGET_CONTROLLER
