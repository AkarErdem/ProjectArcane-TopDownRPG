// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ArcaneHUD.generated.h"

class UArcaneUserWidget;

UCLASS()
class ARCANE_API AArcaneHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UArcaneUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UArcaneUserWidget> OverlayWidgetClass;
};
