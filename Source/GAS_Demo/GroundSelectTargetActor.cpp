// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundSelectTargetActor.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/OverlapResult.h"
#include "Kismet/GameplayStatics.h"

void AGroundSelectTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	PrimaryPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AGroundSelectTargetActor::ConfirmTargetingAndContinue()
{
	FVector LookPoint;
	GetPlayerLookAtPoint(LookPoint);
	TArray<FOverlapResult> OverlapResults;
	TArray<TWeakObjectPtr<AActor>> OverlapActors;

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	QueryParams.bReturnPhysicalMaterial = false;
	APawn* SelfPawn = PrimaryPC->GetPawn();

	if(SelfPawn)
	{
		QueryParams.AddIgnoredActor(SelfPawn);
	}

	bool QueryResult = GetWorld()->OverlapMultiByObjectType(OverlapResults,LookPoint,FQuat::Identity,FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),FCollisionShape::MakeSphere(SelectRadius),QueryParams);
	
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
	
	FGameplayAbilityTargetDataHandle TargetDataHandle;
	
	FGameplayAbilityTargetData_LocationInfo* CenterLoc = new FGameplayAbilityTargetData_LocationInfo();
	CenterLoc->TargetLocation.LiteralTransform = FTransform(LookPoint);
	CenterLoc->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;

	// 看向的地方负载
	TargetDataHandle.Add(CenterLoc);

	//选中的敌人负载
	if(OverlapActors.Num() > 0)
	{
		FGameplayAbilityTargetData_ActorArray* ActorArray = new FGameplayAbilityTargetData_ActorArray();
		ActorArray->SetActors(OverlapActors);

		TargetDataHandle.Add(ActorArray);
	}

	check(ShouldProduceTargetData());
	if(IsConfirmTargetingAllowed())
	{
		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
	
}

bool AGroundSelectTargetActor::GetPlayerLookAtPoint(FVector& Out_LookPoint)
{
	FVector ViewLoc;
	FRotator ViewRot;
	PrimaryPC->GetPlayerViewPoint(ViewLoc, ViewRot);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	APawn* SelfPawn = PrimaryPC->GetPawn();
	if(SelfPawn)
	{
		QueryParams.AddIgnoredActor(SelfPawn);
	}
	
	bool TraceResult = GetWorld()->LineTraceSingleByChannel(HitResult,ViewLoc,ViewLoc+ViewRot.Vector()*5000.0f,ECollisionChannel::ECC_Visibility,QueryParams);
	
	if(TraceResult)
	{
		Out_LookPoint = HitResult.ImpactPoint;
	}
	
	return TraceResult;
}
