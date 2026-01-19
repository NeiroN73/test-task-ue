// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "StagedControllerFragment.h"

#include "OverlapFragment.h"
#include "ProjectCoreRuntime/Fragments/Base/FragmentsContainer.h"
#include "ProjectCoreRuntime/Services/TweensService.h"
#include "TestTaskUE/Configs/ElevatorsJsonConfig.h"

void UStagedControllerFragment::Inject(UInstallerContainer* Container)
{
	TweensService = Container->Resolve<UTweensService>();
}

void UStagedControllerFragment::ProcessFragmentsFromContainer(UFragmentsContainer* InFragmentsContainer)
{
	if (auto Fragment = InFragmentsContainer->TryGetFragment<UOverlapFragment>())
	{
		Fragment->OnOverlapBegan.AddUObject(this, &UStagedControllerFragment::OnBoxOverlaped);
	}
}

void UStagedControllerFragment::Configure(AActor* InActor, const FStagedMoveParams* InElevatorsJsonConfig)
{
	Actor = InActor;
	StagedMoveParams = *InElevatorsJsonConfig;
}

void UStagedControllerFragment::OnBoxOverlaped(AActor* OtherActor)
{
	if (Cast<APawn>(OtherActor))
	{
		if (!TweensService->IsTweening(MoveTweenHandle))
		{
			Move();
		}
	}
}

void UStagedControllerFragment::Move()
{
	// Проверяем, что все длительности одинаковы
	auto Stages = StagedMoveParams.Stages;
	if (Stages.Num() == 0) return;
    
	float FirstDuration = Stages[0].Duration;
	for (const auto& Stage : Stages)
	{
		if (!FMath::IsNearlyEqual(Stage.Duration, FirstDuration))
		{
			UE_LOG(LogTemp, Warning, TEXT("Stage durations are not equal! Speed will not be synchronized."));
			break;
		}
	}
    
	// Оригинальный расчет остается
	FVector StartPos = Actor->GetActorLocation();
	Positions.SetNum(Stages.Num());
    
	for (int32 i = 0; i < Stages.Num(); i++)
	{
		float Alpha = GetEasedAlpha(
			(float)(i + 1), Stages.Num(),
			Stages[i].EaseType
		);
		Positions[i] = FMath::Lerp(StartPos, StartPos + StagedMoveParams.Position, Alpha);
	}
    
	CurrentStageIndex = -1;
	MoveRecursive();
}

float UStagedControllerFragment::GetEasedAlpha(float CurrentTime, float Duration, ETweenEaseType EaseType)
{
	auto Alpha = Duration < 0 ? 1.0f : FMath::Clamp(CurrentTime / Duration, 0.f, 1.f);
	switch(EaseType)
	{
		case ETweenEaseType::EaseIn: return FMath::InterpEaseIn(0.f, 1.f, Alpha, 2.f);
		case ETweenEaseType::EaseOut: return FMath::InterpEaseOut(0.f, 1.f, Alpha, 2.f);
		case ETweenEaseType::EaseInOut: return FMath::InterpEaseInOut(0.f, 1.f, Alpha, 2.f);
		default: return Alpha;
	}
}

void UStagedControllerFragment::MoveRecursive()
{
	auto Stages = StagedMoveParams.Stages;
    
	// if (bReversed)
	// {
	// 	CurrentStageIndex--;
	// 	if (CurrentStageIndex < 0)
	// 	{
	// 		bReversed = false;
	// 	}
	// }
	// else
	// {
	// 	CurrentStageIndex++;
	// 	if (CurrentStageIndex >= Stages.Num())
	// 	{
	// 		bReversed = true;
	// 	}
	// }

	CurrentStageIndex++;
    
	if (!Stages.IsValidIndex(CurrentStageIndex))
	{
		CurrentStageIndex = FMath::Clamp(CurrentStageIndex, 0, Stages.Num() - 1);
	}
    
	const auto& Stage = Stages[CurrentStageIndex];
    
	MoveTweenHandle = TweensService->CreateMoveTween(
		Actor.Get(), 
		Positions[CurrentStageIndex], 
		Stage.Duration)
		.SetEaseType(Stage.EaseType)
		.OnComplete(FSimpleDelegate::CreateUObject(this, &UStagedControllerFragment::MoveRecursive))
		.Build();
}
