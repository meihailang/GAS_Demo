// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GAS_DEMO_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MyAttributeSet")
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, HP);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MyAttributeSet")
	FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxHP);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MyAttributeSet")
	FGameplayAttributeData MP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MP);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MyAttributeSet")
	FGameplayAttributeData MaxMP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxMP);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MyAttributeSet")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Strength);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MyAttributeSet")
	FGameplayAttributeData MaxStrength;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxStrength);
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
	
};
