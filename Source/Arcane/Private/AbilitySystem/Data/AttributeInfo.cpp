// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/Data/AttributeInfo.h"

FArcaneAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, const bool bLogNotFound) const
{
	if(!AttributeInformation.Contains(AttributeTag))
	{
		if(bLogNotFound)
		{
			UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
		}
		return FArcaneAttributeInfo();
	}

	return AttributeInformation[AttributeTag];
}
