// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "ProjectCoreRuntime/Fragments/Base/Fragment.h"
#include "ProjectCoreRuntime/Interfaces/Initializable.h"
#include "TestTaskUE/Configs/ElevatorsJsonConfig.h"
#include "StagedMoveFragment.generated.h"

class UTweensService;
class UElevatorsJsonConfig;

UCLASS()
class TESTTASKUE_API UStagedMoveFragment : public UFragment,
	public IInjectable,
	public IInitializable
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
	FVector StartPosition;
	FVector EndPosition;

public:
	virtual void Inject(UInstallerContainer* Container) override;
	virtual void ProcessFragmentsFromContainer(UFragmentsContainer* InFragmentsContainer) override;
	void Configure(AActor* Actor, const FStagedMoveParams* InElevatorsJsonConfig);
	void OnBoxOverlaped(AActor* OtherActor);
	void Move();
	void MoveRecursively();
	virtual void Initialize() override;
};