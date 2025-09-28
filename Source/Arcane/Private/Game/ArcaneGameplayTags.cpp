// Copyright (c) 2025 Erdem Akar

#include "Game/ArcaneGameplayTags.h"

namespace ArcaneGameplayTags
{
	// Primary
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Primary_Strength, "Attributes.Primary.Strength", "Increases physical power and melee damage.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Primary_Intelligence, "Attributes.Primary.Intelligence", "Increases magical power and spell damage.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Primary_Resilience, "Attributes.Primary.Resilience", "Improves armor and resistance against damage.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Primary_Vigor, "Attributes.Primary.Vigor", "Increases maximum health.");

	// Secondary
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_Armor, "Attributes.Secondary.Armor", "Reduces incoming physical damage.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_ArmorPenetration, "Attributes.Secondary.ArmorPenetration", "Bypasses a portion of enemy armor.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_BlockChance, "Attributes.Secondary.BlockChance", "Chance to block incoming attacks.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_CriticalHitChance, "Attributes.Secondary.CriticalHitChance", "Chance to deal a critical strike.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_CriticalHitDamage, "Attributes.Secondary.CriticalHitDamage", "Bonus damage dealt on critical hits.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_CriticalHitResistance, "Attributes.Secondary.CriticalHitResistance", "Reduces chance of receiving critical hits.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_HealthRegeneration, "Attributes.Secondary.HealthRegeneration", "Rate at which health restores over time.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_ManaRegeneration, "Attributes.Secondary.ManaRegeneration", "Rate at which mana restores over time.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_MaxHealth, "Attributes.Secondary.MaxHealth", "Maximum health capacity.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_MaxMana, "Attributes.Secondary.MaxMana", "Maximum mana capacity.");

	// Vitals
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Vitals_Health, "Attributes.Vitals.Health", "Amount of damage a character can take before death.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Vitals_Mana, "Attributes.Vitals.Mana", "Current mana value.");

	const TMap<FGameplayTag, FGameplayTag> Map =
	{
		/*{ Key_Tag_One, Value_Tag_One },
		{ Key_Tag_Two, Value_Tag_Two }*/
	};
}
