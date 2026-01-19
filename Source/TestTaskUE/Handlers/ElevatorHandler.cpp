// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ElevatorHandler.h"

#include "Components/BoxComponent.h"
#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Fragments/Base/FragmentsContainer.h"
#include "TestTaskUE/Components/ElevatorPreviewComponent.h"
#include "TestTaskUE/Configs/ElevatorsJsonConfig.h"
#include "TestTaskUE/Fragments/OverlapFragment.h"
#include "TestTaskUE/Fragments/StagedMoveFragment.h"

AElevatorHandler::AElevatorHandler()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetGenerateOverlapEvents(true);
	OverlapBox->SetupAttachment(RootComponent);

#if WITH_EDITOR
	ElevatorPreview = CreateDefaultSubobject<UElevatorPreviewComponent>(TEXT("ElevatorPreview"));
	ElevatorPreview->SetupAttachment(RootComponent);
#endif
}

void AElevatorHandler::Inject(UInstallerContainer* Container)
{
	ElevatorsJsonConfig = Container->Resolve<UElevatorsJsonConfig>();
}

void AElevatorHandler::BuildFragments(UFragmentsContainer* FragmentsContainer)
{
	if (auto Fragment = FragmentsContainer->TryAddFragment<UStagedMoveFragment>())
	{
		Fragment->Configure(this, ElevatorsJsonConfig->GetElevatorParamsByTag(Tag));
	}
	if (auto Fragment = FragmentsContainer->TryAddFragment<UOverlapFragment>())
	{
		Fragment->Configure(OverlapBox.Get());
	}
}
