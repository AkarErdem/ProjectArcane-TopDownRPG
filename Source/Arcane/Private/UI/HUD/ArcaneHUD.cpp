// Copyright (c) 2025 Erdem Akar

#include "UI/HUD/ArcaneHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/ArcaneUserWidget.h"

void AArcaneHUD::BeginPlay()
{
	Super::BeginPlay();

	UArcaneUserWidget* Widget = CreateWidget<UArcaneUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();

}
