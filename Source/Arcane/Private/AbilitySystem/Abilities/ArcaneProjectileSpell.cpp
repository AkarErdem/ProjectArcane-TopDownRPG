// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/Abilities/ArcaneProjectileSpell.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/ArcaneProjectile.h"
#include "Game/ArcaneGameplayTags.h"
#include "Interaction/CombatInterface.h"

void UArcaneProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UArcaneProjectileSpell::SpawnProjectile(const FVector& ProjectileTarget)
{
	const bool IsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if(!IsServer)
	{
		return;
	}

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if(!CombatInterface)
	{
		return;
	}

	const FVector SocketLocation = CombatInterface->GetSocketLocation();
	FRotator Rotation = (ProjectileTarget - SocketLocation).Rotation();
	Rotation.Pitch = 0.f;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());

	AArcaneProjectile* Projectile = GetWorld()->SpawnActorDeferred<AArcaneProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetAvatarActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());

	FArcaneGameplayTags GameplayTags = FArcaneGameplayTags::Get();
	const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Meta_Tag_Damage, ScaledDamage);
	Projectile->DamageEffectSpecHandle = SpecHandle;

	Projectile->FinishSpawning(SpawnTransform);
}
