// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArcaneUserWidget.generated.h"

class UArcaneWidgetController;

UCLASS()
class ARCANE_API UArcaneUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UArcaneWidgetController* InWidgetController);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UArcaneWidgetController> WidgetController;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
};
