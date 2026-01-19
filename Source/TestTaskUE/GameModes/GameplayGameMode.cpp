// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "GameplayGameMode.h"

#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "ProjectCoreRuntime/Installer/InstallerGameSubsystem.h"
#include "ProjectCoreRuntime/Services/TickService.h"
#include "TestTaskUE/Handlers/PlayerHandler.h"


void AGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();

	auto InstallerSubsystem = GetGameInstance()->GetSubsystem<UInstallerGameSubsystem>();
	auto Container = InstallerSubsystem->InstallerContainer;

	auto Worldables = Container->ResolveAllImplements<IWorldable>();
	if (auto InWorld = GetWorld())
	{
		if (!Worldables.IsEmpty())
		{
			for (auto Worldable : Worldables)
			{
				Worldable->WorldChanged(InWorld);
			}
		}
	}
	
	auto HandlersFactory = Container->Resolve<UHandlersFactory>();
	HandlersFactory->SpawnCharacterHandler<APlayerHandler>("player");

	TickService = Container->Resolve<UTickService>();
}

void AGameplayGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickService->OnTick(DeltaTime);
}
