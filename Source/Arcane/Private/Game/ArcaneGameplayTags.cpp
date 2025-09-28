// Copyright (c) 2025 Erdem Akar

#include "Game/ArcaneGameplayTags.h"

#define ADD_NATIVE_TAG(AttributeType, AttributeName, Comment) \
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_##AttributeType##_##AttributeName, *FString((FString("Attributes.") + #AttributeType + FString(".")+#AttributeName)), Comment)

// Primary
ADD_NATIVE_TAG(Primary, Strength, "Increases physical power and melee damage.");
ADD_NATIVE_TAG(Primary, Intelligence, "Increases magical power and spell damage.");
ADD_NATIVE_TAG(Primary, Resilience, "Improves armor and resistance against damage.");
ADD_NATIVE_TAG(Primary, Vitality, "Increases maximum health.");

// Secondary
ADD_NATIVE_TAG(Secondary, Armor, "Reduces incoming physical damage.");
ADD_NATIVE_TAG(Secondary, ArmorPenetration, "Bypasses a portion of enemy armor.");
ADD_NATIVE_TAG(Secondary, BlockChance, "Chance to block incoming attacks.");
ADD_NATIVE_TAG(Secondary, CriticalHitChance, "Chance to deal a critical strike.");
ADD_NATIVE_TAG(Secondary, CriticalHitDamage, "Bonus damage dealt on critical hits.");
ADD_NATIVE_TAG(Secondary, CriticalHitResistance, "Reduces chance of receiving critical hits.");
ADD_NATIVE_TAG(Secondary, HealthRegeneration, "Rate at which health restores over time.");
ADD_NATIVE_TAG(Secondary, ManaRegeneration, "Rate at which mana restores over time.");
ADD_NATIVE_TAG(Secondary, MaxHealth, "Maximum health capacity.");
ADD_NATIVE_TAG(Secondary, MaxMana, "Maximum mana capacity.");

// Vitals
ADD_NATIVE_TAG(Vital, Health, "Amount of damage a character can take before death.");
ADD_NATIVE_TAG(Vital, Mana, "Resource for spells.");

#undef ADD_NATIVE_TAG

FArcaneGameplayTags FArcaneGameplayTags::GameplayTags;

void FArcaneGameplayTags::Initialize()
{
	GameplayTags.ArcaneTagsContainer.Reset();

	// Alternative Solution
#define ADD_TAG_TO_CONTAINER(AttributeType, AttributeName) GameplayTags.ArcaneTagsContainer.AddTag(Attributes_##AttributeType##_##AttributeName);

	ADD_TAG_TO_CONTAINER(Primary, Strength)
	ADD_TAG_TO_CONTAINER(Primary, Intelligence)
	ADD_TAG_TO_CONTAINER(Primary, Resilience)
	ADD_TAG_TO_CONTAINER(Primary, Vitality)

	ADD_TAG_TO_CONTAINER(Secondary, Armor)
	ADD_TAG_TO_CONTAINER(Secondary, ArmorPenetration)
	ADD_TAG_TO_CONTAINER(Secondary, BlockChance)
	ADD_TAG_TO_CONTAINER(Secondary, CriticalHitChance)
	ADD_TAG_TO_CONTAINER(Secondary, CriticalHitDamage)
	ADD_TAG_TO_CONTAINER(Secondary, CriticalHitResistance)
	ADD_TAG_TO_CONTAINER(Secondary, HealthRegeneration)
	ADD_TAG_TO_CONTAINER(Secondary, ManaRegeneration)
	ADD_TAG_TO_CONTAINER(Secondary, MaxHealth)
	ADD_TAG_TO_CONTAINER(Secondary, MaxMana)

	ADD_TAG_TO_CONTAINER(Vital, Health)
	ADD_TAG_TO_CONTAINER(Vital, Mana)

#undef ADD_TAG_TO_CONTAINER
}
