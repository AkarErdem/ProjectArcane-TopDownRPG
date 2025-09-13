// Copyright (c) 2025 Erdem Akar


#include "Character/ArcaneEnemy.h"
#include "Arcane/Arcane.h"

AArcaneEnemy::AArcaneEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AArcaneEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AArcaneEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AArcaneEnemy::HighlightActor()
{
	bHighlighted = true;

	for (TInlineComponentArray<UMeshComponent*> Meshes(this, /*bIncludeFromChildActors*/ true); auto* M : Meshes)
	{
		M->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
		M->SetRenderCustomDepth(true);
	}
}

void AArcaneEnemy::UnHighlightActor()
{
	bHighlighted = false;

	for (TInlineComponentArray<UMeshComponent*> Meshes(this, /*bIncludeFromChildActors*/ true); auto* M : Meshes)
	{
		M->SetRenderCustomDepth(false);
	}
}
