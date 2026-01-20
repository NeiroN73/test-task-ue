// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/StagedMovable.h"
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
public IInitializable,
public IStagedMovable
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
	FOnStateChanged OnStateChanged;
	EStagedMoveState StagedMoveState;

public:
	void Configure(AActor* Actor, const FStagedMoveParams* InElevatorsJsonConfig);
	virtual void Inject(UInstallerContainer* Container) override;
	virtual void Initialize() override;
	virtual void InitializeFragments(UFragmentsContainer* InFragmentsContainer) override;
	virtual FOnStateChanged& GetOnStateChangedDelegate() override;
	virtual EStagedMoveState GetCurrentMoveState() const override;
	void OnBoxOverlaped(AActor* OtherActor);
	void Move();
	void MoveRecursively();
	void TryChangeState(EStagedMoveState InState);
};