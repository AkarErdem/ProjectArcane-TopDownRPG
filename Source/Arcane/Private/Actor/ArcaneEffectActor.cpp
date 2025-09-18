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

void AArcaneEffectActor::ApplyEffect(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		check(GameplayEffectClass);

		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContext);
		const FActiveGameplayEffectHandle ActiveEffectHandle = ASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data, ASC);

		if (EffectSpecHandle.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite &&
			InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			AppliedInfiniteEffects.Add(ActiveEffectHandle, ASC);
		}
	}
}

void AArcaneEffectActor::RemoveInfiniteEffect(AActor* TargetActor)
{
	const UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(ASC))
	{
		return;
	}

	TArray<FActiveGameplayEffectHandle> HandlesToRemove;
	for (auto& Pair : AppliedInfiniteEffects)
	{
		if (!IsValid(Pair.Value) || Pair.Value != ASC)
		{
			continue;
		}
		Pair.Value->RemoveActiveGameplayEffect(Pair.Key, 1);
		HandlesToRemove.Add(Pair.Key);
	}
	for (FActiveGameplayEffectHandle& ToRemove : HandlesToRemove)
	{
		AppliedInfiniteEffects.Remove(ToRemove);
	}
}

void AArcaneEffectActor::OnOverlap(AActor* TargetActor)
{
	for (const FEffect& Effect : Effects)
	{
		if (Effect.Policy == EEffectPolicy::ApplyOnOverlap)
		{
			ApplyEffect(TargetActor, Effect.EffectClass);
		}
	}
}

void AArcaneEffectActor::OnEndOverlap(AActor* TargetActor)
{
	for (const auto& [EffectClass, Policy, RemovalPolicy] : Effects)
	{
		if (Policy == EEffectPolicy::ApplyOnEndOverlap)
		{
			ApplyEffect(TargetActor, EffectClass);
		}

		if (RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			RemoveInfiniteEffect(TargetActor);
		}
	}
}
