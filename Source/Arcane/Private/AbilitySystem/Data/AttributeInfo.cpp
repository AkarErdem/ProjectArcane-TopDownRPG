// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/Data/AttributeInfo.h"

#include "AbilitySystem/ArcaneAttributeSet.h"
#include "Game/ArcaneGameplayTags.h"

FArcaneAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, const bool bLogNotFound) const
{
	for(const auto& Info : AttributeInformation)
	{
		if(Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}
	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}
	return FArcaneAttributeInfo();
}
#if WITH_EDITOR
void UAttributeInfo::PopulateDataAsset()
{
	FArcaneGameplayTags::Initialize();

	const FArcaneGameplayTags GameplayTags = FArcaneGameplayTags::Get();
	AttributeInformation.Empty();
	AttributeInformation.SetNumZeroed(GameplayTags.ArcaneTagsContainer.Num());

	for(int i = 0; i < GameplayTags.ArcaneTagsContainer.Num(); ++i)
	{
		const FGameplayTag IndexTag = GameplayTags.ArcaneTagsContainer.GetByIndex(i);
		AttributeInformation[i].AttributeTag = IndexTag; // Set AttributeTag

		const FGameplayTagNode* TagNode = UGameplayTagsManager::Get().FindTagNode(IndexTag).Get(); // Get the last noe of the GameplayTag
		FString NodeString = FName::NameToDisplayString(TagNode->GetSimpleTagName().ToString(), /*bIsBool*/ false); // Get node name (i. e. Attribute.Primary. Strength returns Strength) and make it display ready
		AttributeInformation[i].AttributeName = FText::FromString(NodeString); // Set AttributeName

		// Set AttributesToGet
		for(TFieldIterator<FProperty> It(UArcaneAttributeSet::StaticClass()); It; ++It)
		{
			if(FGameplayAttribute::IsGameplayAttributeDataProperty(*It) && FGameplayAttribute(*It).GetName() == TagNode->GetSimpleTagName().ToString())
			{
				AttributeInformation[i].AttributeGetter = FGameplayAttribute(*It);
				break;
			}
		}
		const FName TagName = IndexTag.GetTagName();
		/** OUT's */
		FString TagComment = FString();
		FName TagSource = FName();
		bool bIsTagExplicit = false;
		bool bIsRestrictedTag = false;
		bool bAllowNonRestrictedChildren = false;

		UGameplayTagsManager::Get().GetTagEditorData(
			TagName,
			TagComment,
			TagSource,
			bIsTagExplicit,
			bIsRestrictedTag,
			bAllowNonRestrictedChildren);
		AttributeInformation[i].AttributeDescription = FText::FromString(TagComment); // Set AttributeDescription
	}
}
#endif WITH_EDITOR
