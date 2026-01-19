// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "StagedMoveFragment.h"

#include "OverlapFragment.h"
#include "ProjectCoreRuntime/Fragments/Base/FragmentsContainer.h"
#include "ProjectCoreRuntime/Services/TweensService.h"
#include "TestTaskUE/Configs/ElevatorsJsonConfig.h"

void UStagedMoveFragment::Configure(AActor* InActor, const FStagedMoveParams* InElevatorsJsonConfig)
{
	Actor = InActor;
	StagedMoveParams = *InElevatorsJsonConfig;
}

void UStagedMoveFragment::Inject(UInstallerContainer* Container)
{
	TweensService = Container->Resolve<UTweensService>();
}

void UStagedMoveFragment::Initialize()
{
	StartPosition = Actor->GetActorLocation();
	EndPosition = Actor->GetActorLocation() + StagedMoveParams.Position;
}

void UStagedMoveFragment::ProcessFragmentsFromContainer(UFragmentsContainer* InFragmentsContainer)
{
	if (auto Fragment = InFragmentsContainer->TryGetFragment<UOverlapFragment>())
	{
		Fragment->OnOverlapBegan.AddUObject(this, &UStagedMoveFragment::OnBoxOverlaped);
	}
}

void UStagedMoveFragment::OnBoxOverlaped(AActor* OtherActor)
{
	if (Cast<APawn>(OtherActor))
	{
		if (!TweensService->IsTweening(MoveTweenHandle))
		{
			Move();
		}
	}
}

void UStagedMoveFragment::Move()
{
	auto Stages = StagedMoveParams.Stages;
	if (Stages.Num() == 0)
		return;

	Positions.SetNum(Stages.Num());
	MaxDuration = 0;

	for (int32 i = 0; i < Stages.Num(); i++)
	{
		MaxDuration += Stages[i].Duration;
	}

	float DurationSum = 0;
	auto TargetPosition = bReversed ? StartPosition : EndPosition;
	auto ActorPosition = Actor->GetActorLocation();
	
	for (int32 i = 0; i < Stages.Num(); i++)
	{
		DurationSum += Stages[i].Duration;
		Positions[i] = FMath::Lerp(ActorPosition,TargetPosition,DurationSum / MaxDuration);
	}
    
	CurrentStageIndex = -1;
	MoveRecursively();
}

void UStagedMoveFragment::MoveRecursively()
{
	auto Stages = StagedMoveParams.Stages;

	CurrentStageIndex++;
	
	if (CurrentStageIndex >= Stages.Num())
	{
		bReversed = !bReversed;
		TweensService->KillTween(MoveTweenHandle);
		return;
	}
    
	const auto& Stage = Stages[CurrentStageIndex];
    
	MoveTweenHandle = TweensService->CreateMoveTween(
		Actor.Get(), 
		Positions[CurrentStageIndex], 
		Stage.Duration)
		.SetEaseType(Stage.EaseType)
		.OnComplete(FSimpleDelegate::CreateUObject(this, &UStagedMoveFragment::MoveRecursively))
		.Build();
}