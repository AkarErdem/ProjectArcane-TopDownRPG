// Copyright (c) 2025 Erdem Akar

#include "Game/ArcaneGameplayTags.h"

#define ADD_NATIVE_TAG(NameOne, NameTwo, NameThree, Comment) \
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(NameOne##_##NameTwo##_##NameThree, *FString(FString(#NameOne) + "." + #NameTwo + "." + #NameThree), Comment)

#define ADD_ATTRIBUTE_TAG(AttributeType, AttributeName, Comment) \
	ADD_NATIVE_TAG(Attributes, AttributeType, AttributeName, Comment)

// Primary
ADD_ATTRIBUTE_TAG(Primary, Strength, "Increases physical power and melee damage.");
ADD_ATTRIBUTE_TAG(Primary, Intelligence, "Increases magical power and spell damage.");
ADD_ATTRIBUTE_TAG(Primary, Resilience, "Improves armor and resistance against damage.");
ADD_ATTRIBUTE_TAG(Primary, Vitality, "Increases maximum health.");

// Secondary
ADD_ATTRIBUTE_TAG(Secondary, Armor, "Reduces incoming physical damage.");
ADD_ATTRIBUTE_TAG(Secondary, ArmorPenetration, "Bypasses a portion of enemy armor.");
ADD_ATTRIBUTE_TAG(Secondary, BlockChance, "Chance to block incoming attacks.");
ADD_ATTRIBUTE_TAG(Secondary, CriticalHitChance, "Chance to deal a critical strike.");
ADD_ATTRIBUTE_TAG(Secondary, CriticalHitDamage, "Bonus damage dealt on critical hits.");
ADD_ATTRIBUTE_TAG(Secondary, CriticalHitResistance, "Reduces chance of receiving critical hits.");
ADD_ATTRIBUTE_TAG(Secondary, HealthRegeneration, "Rate at which health restores over time.");
ADD_ATTRIBUTE_TAG(Secondary, ManaRegeneration, "Rate at which mana restores over time.");
ADD_ATTRIBUTE_TAG(Secondary, MaxHealth, "Maximum health capacity.");
ADD_ATTRIBUTE_TAG(Secondary, MaxMana, "Maximum mana capacity.");

// Vitals
ADD_ATTRIBUTE_TAG(Vital, Health, "Amount of damage a character can take before death.");
ADD_ATTRIBUTE_TAG(Vital, Mana, "Resource for spells.");

// Inputs
ADD_NATIVE_TAG(Inputs, Tag, LMB, "");
ADD_NATIVE_TAG(Inputs, Tag, RMB, "");
ADD_NATIVE_TAG(Inputs, Tag, 1, "");
ADD_NATIVE_TAG(Inputs, Tag, 2, "");
ADD_NATIVE_TAG(Inputs, Tag, 3, "");
ADD_NATIVE_TAG(Inputs, Tag, 4, "");

#undef ADD_ATTRIBUTE_TAG

FArcaneGameplayTags FArcaneGameplayTags::GameplayTags;

void FArcaneGameplayTags::Initialize()
{
	GameplayTags.ArcaneTagsContainer.Reset();

#define ADD_TAG_TO_CONTAINER(NameOne, NameTwo, NameThree) GameplayTags.ArcaneTagsContainer.AddTag(NameOne##_##NameTwo##_##NameThree);

	ADD_TAG_TO_CONTAINER(Attributes, Primary, Strength)
	ADD_TAG_TO_CONTAINER(Attributes, Primary, Intelligence)
	ADD_TAG_TO_CONTAINER(Attributes, Primary, Resilience)
	ADD_TAG_TO_CONTAINER(Attributes, Primary, Vitality)

	ADD_TAG_TO_CONTAINER(Attributes, Secondary, Armor)
	ADD_TAG_TO_CONTAINER(Attributes, Secondary, ArmorPenetration)
	ADD_TAG_TO_CONTAINER(Attributes, Secondary, BlockChance)
	ADD_TAG_TO_CONTAINER(Attributes, Secondary, CriticalHitChance)
	ADD_TAG_TO_CONTAINER(Attributes, Secondary, CriticalHitDamage)
	ADD_TAG_TO_CONTAINER(Attributes, Secondary, CriticalHitResistance)
	ADD_TAG_TO_CONTAINER(Attributes, Secondary, HealthRegeneration)
	ADD_TAG_TO_CONTAINER(Attributes, Secondary, ManaRegeneration)
	ADD_TAG_TO_CONTAINER(Attributes, Secondary, MaxHealth)
	ADD_TAG_TO_CONTAINER(Attributes, Secondary, MaxMana)

	ADD_TAG_TO_CONTAINER(Attributes, Vital, Health)
	ADD_TAG_TO_CONTAINER(Attributes, Vital, Mana)

	ADD_TAG_TO_CONTAINER(Inputs, Tag, LMB)
	ADD_TAG_TO_CONTAINER(Inputs, Tag, RMB)
	ADD_TAG_TO_CONTAINER(Inputs, Tag, 1)
	ADD_TAG_TO_CONTAINER(Inputs, Tag, 2)
	ADD_TAG_TO_CONTAINER(Inputs, Tag, 3)
	ADD_TAG_TO_CONTAINER(Inputs, Tag, 4)

#undef ADD_TAG_TO_CONTAINER
}
