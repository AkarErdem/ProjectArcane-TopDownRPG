// Copyright (c) 2025 Erdem Akar

#include "Actor/ArcaneEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AArcaneEffectActor::AArcaneEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(SceneRoot);
}

void AArcaneEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddSourceObject(TargetActor);

		const FGameplayEffectSpecHandle EffectSpec = ASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContext);
		ASC->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data);
	}
}
