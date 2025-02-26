// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "AbilitySystemComponent.h"
#include "MyAttributeSet.h"
#include "MyGameplayAbility.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UAbilitySystemComponent* MyAbilitySystemComponent = this->FindComponentByClass<UAbilitySystemComponent>();
	if(MyAbilitySystemComponent)
	{
		MyAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UMyAttributeSet::GetHPAttribute()).AddUObject(this,&AMyCharacter::OnHPAtrributeChanged);
		MyAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UMyAttributeSet::GetMPAttribute()).AddUObject(this,&AMyCharacter::OnMPAtributeChanged);
		MyAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UMyAttributeSet::GetStrengthAttribute()).AddUObject(this,&AMyCharacter::OnStrengthAtributeChanged);
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::OnHPAtrributeChanged(const FOnAttributeChangeData& Data)
{
	HPChangeEvent.Broadcast(Data.NewValue);
}

void AMyCharacter::OnMPAtributeChanged(const FOnAttributeChangeData& Data)
{
	MPChangeEvent.Broadcast(Data.NewValue);
}

void AMyCharacter::OnStrengthAtributeChanged(const FOnAttributeChangeData& Data)
{
	StrengthChangeEvent.Broadcast(Data.NewValue);
}

FGameplayAbilityInfo AMyCharacter::GameplayAbilityInfo(TSubclassOf<UMyGameplayAbility> AbilityClass, int Level)
{
	UAbilitySystemComponent* MyAbilitySystemComponent = this->FindComponentByClass<UAbilitySystemComponent>();
	UMyGameplayAbility* AbilityInstance = AbilityClass->GetDefaultObject<UMyGameplayAbility>();
	if(MyAbilitySystemComponent&&AbilityInstance)
	{
		return AbilityInstance->GetGameplayAbilityInfo(Level);
	}
	return FGameplayAbilityInfo();
}

