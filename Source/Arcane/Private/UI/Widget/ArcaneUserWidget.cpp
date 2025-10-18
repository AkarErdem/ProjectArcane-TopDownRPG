// Copyright (c) 2025 Erdem Akar

#include "UI/Widget/ArcaneUserWidget.h"

void UArcaneUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	OnWidgetControllerSet();
}
