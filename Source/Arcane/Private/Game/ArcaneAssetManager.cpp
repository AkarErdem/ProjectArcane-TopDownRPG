// Copyright (c) 2025 Erdem Akar

#include "Game/ArcaneAssetManager.h"

UArcaneAssetManager& UArcaneAssetManager::Get()
{
	check(GEngine);

	UArcaneAssetManager* ArcaneAssetManager = Cast<UArcaneAssetManager>(GEngine->AssetManager);
	return *ArcaneAssetManager;
}

void UArcaneAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
}
