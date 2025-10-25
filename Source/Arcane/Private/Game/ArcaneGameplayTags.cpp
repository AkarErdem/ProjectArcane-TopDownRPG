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

// Meta
ADD_NATIVE_TAG(Meta, Tag, Damage, "Applied to a character for reducing health.");

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

	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Primary_Strength);
	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Primary_Intelligence);
	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Primary_Resilience);
	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Primary_Vitality);

	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Secondary_Armor);
	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Secondary_ArmorPenetration);
	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Secondary_BlockChance);
	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Secondary_CriticalHitChance);
	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Secondary_CriticalHitDamage);
	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Secondary_CriticalHitResistance);
	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Secondary_HealthRegeneration);
	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Secondary_ManaRegeneration);
	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Secondary_MaxHealth);
	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Secondary_MaxMana);

	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Vital_Health);
	 GameplayTags.ArcaneTagsContainer.AddTag(Attributes_Vital_Mana);

	 GameplayTags.ArcaneTagsContainer.AddTag(Inputs_Tag_LMB);
	 GameplayTags.ArcaneTagsContainer.AddTag(Inputs_Tag_RMB);
	 GameplayTags.ArcaneTagsContainer.AddTag(Inputs_Tag_1);
	 GameplayTags.ArcaneTagsContainer.AddTag(Inputs_Tag_2);
	 GameplayTags.ArcaneTagsContainer.AddTag(Inputs_Tag_3);
	 GameplayTags.ArcaneTagsContainer.AddTag(Inputs_Tag_4);

	 GameplayTags.ArcaneTagsContainer.AddTag(Meta_Tag_Damage);
}