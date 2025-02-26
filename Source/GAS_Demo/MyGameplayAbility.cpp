// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameplayAbility.h"

FGameplayAbilityInfo::FGameplayAbilityInfo():
	CD(0),
	CostType(ECostType::MP),
	CostValue(0),
	IconMaterial(nullptr),
	AbilityClass(nullptr)
{
	
}

FGameplayAbilityInfo::FGameplayAbilityInfo(float CD, ECostType CostType, float CostValue,
	UMaterialInstance* IconMaterial, TSubclassOf<UMyGameplayAbility> AbilityClass):
	CD(CD),
	CostValue(CostValue),
	CostType(CostType),
	IconMaterial(IconMaterial),
	AbilityClass(AbilityClass)
{
	
}

FGameplayAbilityInfo UMyGameplayAbility::GetGameplayAbilityInfo(int Level)
{
	UGameplayEffect* CDEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();
	float CD = 0;
	float CostValue = 0;
	ECostType CostType = ECostType::MP;
	if(CDEffect&&CostEffect)
	{
		CDEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(Level,CD);
		if(CostEffect->Modifiers.Num()>0)
		{
			FGameplayModifierInfo CostEffectModifierInfo = CostEffect->Modifiers[0];
			CostEffectModifierInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(Level,CostValue);
			FString CostTypeName = CostEffectModifierInfo.Attribute.AttributeName;

			if(CostTypeName == "HP")
			{
				CostType = ECostType::HP;
			}
			if(CostTypeName == "MP")
			{
				CostType = ECostType::MP;
			}
			if(CostTypeName == "Strength")
			{
				CostType = ECostType::Strength;
			}
			return FGameplayAbilityInfo(CD,CostType,CostValue,IconMaterial,GetClass());
		}
	}
	return FGameplayAbilityInfo();
}
