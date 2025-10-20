// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass Class)
{
	return CharacterClassInformation.FindChecked(Class);
}
