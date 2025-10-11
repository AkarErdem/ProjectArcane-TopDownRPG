// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/Abilities/ArcaneProjectileSpell.h"
#include "Actor/ArcaneProjectile.h"
#include "Interaction/CombatInterface.h"

void UArcaneProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const bool IsServer = HasAuthority(&ActivationInfo);
	if(!IsServer)
	{
		return;
	}

	if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		// TODO: Set projectile rotation

		AArcaneProjectile* Projectile = GetWorld()->SpawnActorDeferred<AArcaneProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetAvatarActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		// TODO: Give the Projectile a Gameplay Effect Spec for causing damage

		Projectile->FinishSpawning(SpawnTransform);
	}
}
