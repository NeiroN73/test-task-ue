// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ElevatorHandler.h"

#include "Components/BoxComponent.h"
#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Fragments/Base/FragmentsContainer.h"
#include "TestTaskUE/Configs/ElevatorsJsonConfig.h"
#include "TestTaskUE/Fragments/OverlapFragment.h"
#include "TestTaskUE/Fragments/StagedActorMoveFragment.h"
#include "TestTaskUE/Fragments/StagedControllerFragment.h"
#include "TestTaskUE/Fragments/Base/ControllerMovable.h"

AElevatorHandler::AElevatorHandler()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetGenerateOverlapEvents(true);
	OverlapBox->SetupAttachment(RootComponent);
}

void AElevatorHandler::Inject(UInstallerContainer* Container)
{
	ElevatorsJsonConfig = Container->Resolve<UElevatorsJsonConfig>();
}

void AElevatorHandler::BuildFragments(UFragmentsContainer* FragmentsContainer)
{
	if (auto Fragment = FragmentsContainer->TryAddFragmentByInterfaces<UStagedControllerFragment>(
		{UControllerMovable::StaticClass()}))
	{
		Fragment->Configure(this, ElevatorsJsonConfig->GetElevatorParamsByTag(Tag));
	}
	if (auto Fragment = FragmentsContainer->TryAddFragment<UStagedActorMoveFragment>())
	{
	}
	if (auto Fragment = FragmentsContainer->TryAddFragment<UOverlapFragment>())
	{
		Fragment->Configure(OverlapBox.Get());
	}
}
