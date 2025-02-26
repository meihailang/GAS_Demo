// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"
class UMyGameplayAbility;
struct FGameplayAbilityInfo;
struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChangeEvent, float, NewValue);

UCLASS()
class GAS_DEMO_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnValueChangeEvent HPChangeEvent;

	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnValueChangeEvent MPChangeEvent;

	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnValueChangeEvent StrengthChangeEvent;

	void OnHPAtrributeChanged(const FOnAttributeChangeData& Data);

	void OnMPAtributeChanged(const FOnAttributeChangeData& Data);

	void OnStrengthAtributeChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintCallable, Category="MyCharacter")
	FGameplayAbilityInfo GameplayAbilityInfo(TSubclassOf<UMyGameplayAbility>AbilityClass,int Level);
};
