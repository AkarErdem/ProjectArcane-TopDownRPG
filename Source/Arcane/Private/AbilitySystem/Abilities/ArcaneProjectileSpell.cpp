// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/Abilities/ArcaneProjectileSpell.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Actor/ArcaneProjectile.h"
#include "Interaction/CombatInterface.h"

void UArcaneProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UArcaneProjectileSpell::SpawnProjectile() const
{
	const bool IsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if(!IsServer)
	{
		return;
	}

	if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetSocketLocation();
		const FQuat SocketRotation = CombatInterface->GetSocketRotator().Quaternion();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(SocketRotation);

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
