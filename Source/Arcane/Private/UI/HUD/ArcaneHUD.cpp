// Copyright (c) 2025 Erdem Akar

#include "UI/HUD/ArcaneHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/ArcaneUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AArcaneHUD::GetOverlayWidgetController(const FWidgetControllerData& Data)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerData(Data);
	}
	return OverlayWidgetController;
}

void AArcaneHUD::InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState,
	UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass uninitialized, fill out BP_ArcaneHUD."));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass uninitialized, fill out BP_ArcaneHUD."));

	const auto Data = FWidgetControllerData(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(Data);

	OverlayWidget = CreateWidget<UArcaneUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->SetWidgetController(WidgetController);
	OverlayWidget->AddToViewport();
}
