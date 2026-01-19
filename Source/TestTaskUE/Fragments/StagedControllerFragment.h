// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "ProjectCoreRuntime/Fragments/Base/Fragment.h"
#include "TestTaskUE/Configs/ElevatorsJsonConfig.h"
#include "StagedControllerFragment.generated.h"

class UTweensService;
class UElevatorsJsonConfig;

UCLASS()
class TESTTASKUE_API UStagedControllerFragment : public UFragment,
public IInjectable
{
	GENERATED_BODY()

private:
	UPROPERTY()
	FStagedMoveParams StagedMoveParams;
	UPROPERTY()
	TWeakObjectPtr<AActor> Actor;
	UPROPERTY()
	TWeakObjectPtr<UTweensService> TweensService;

	FTweenHandle MoveTweenHandle;
	float MaxDuration;
	int32 CurrentStageIndex;
	TArray<FVector> Positions;
	bool bReversed;
	
public:
	virtual void ProcessFragmentsFromContainer(UFragmentsContainer* InFragmentsContainer) override;
	void Configure(AActor* Actor, const FStagedMoveParams* InElevatorsJsonConfig);
	void OnBoxOverlaped(AActor* OtherActor);
	void Move();
	void MoveRecursive();
	float GetEasedAlpha(float CurrentTime, float Duration, ETweenEaseType EaseType);
	virtual void Inject(UInstallerContainer* Container) override;
};
