// Fill out your copyright notice in the Description page of Project Settings.


#include "AroundTargetActor.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/OverlapResult.h"

void AAroundTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	PrimaryPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
	bDestroyOnConfirmation = false;
}

void AAroundTargetActor::ConfirmTargetingAndContinue()
{
	APawn* SelfPawn = PrimaryPC->GetPawn();
	if(!SelfPawn)
	{
		return;
	}	
	FVector LookPoint = SelfPawn->GetActorLocation();
	TArray<FOverlapResult> OverlapResults;
	TArray<TWeakObjectPtr<AActor>> OverlapActors;

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	QueryParams.bReturnPhysicalMaterial = false;

	if(SelfPawn)
	{
		QueryParams.AddIgnoredActor(SelfPawn);
	}

	bool QueryResult = GetWorld()->OverlapMultiByObjectType(OverlapResults,LookPoint,FQuat::Identity,FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),FCollisionShape::MakeSphere(AroundRadius),QueryParams);
	
	if(QueryResult)
	{
		for(int i = 0; i < OverlapResults.Num(); i++)
		{
			APawn* Enemy = Cast<APawn>(OverlapResults[i].GetActor());
			if(Enemy&&!OverlapActors.Contains(Enemy))
			{
				OverlapActors.Add(Enemy);
			}
		}
	}
	
	FGameplayAbilityTargetDataHandle* TargetDataHandle = new FGameplayAbilityTargetDataHandle();

	//选中的敌人负载
	if(OverlapActors.Num() > 0)
	{
		FGameplayAbilityTargetData_ActorArray* ActorArray = new FGameplayAbilityTargetData_ActorArray();
		ActorArray->SetActors(OverlapActors);

		TargetDataHandle->Add(ActorArray);
	}

	check(ShouldProduceTargetData());
	if(IsConfirmTargetingAllowed())
	{
		TargetDataReadyDelegate.Broadcast(*TargetDataHandle);
	}
}
