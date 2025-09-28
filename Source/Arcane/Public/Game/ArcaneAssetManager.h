// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ArcaneAssetManager.generated.h"

UCLASS()
class ARCANE_API UArcaneAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UArcaneAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
