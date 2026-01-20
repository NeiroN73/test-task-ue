// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "InstallerGameMode.h"

#include "ProjectCoreRuntime/DependencyInjection/FactoriesLocator.h"
#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Installer/InstallerGameSubsystem.h"
#include "ProjectCoreRuntime/Interfaces/Initializable.h"
#include "ProjectCoreRuntime/Services/TickService.h"
#include "TestTaskUE/Scopes/ProjectInstallerScope.h"

AInstallerGameMode::AInstallerGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInstallerGameMode::InitializeScope(UConfigs* Configs)
{
	auto InstallerSubsystem = GetGameInstance()->GetSubsystem<UInstallerGameSubsystem>();
	if (InstallerSubsystem->InstallerContainer == nullptr)
	{
		auto InstallerScope = NewObject<UProjectInstallerScope>();
		InstallerContainer = NewObject<UInstallerContainer>();
		if (Configs != nullptr)
		{
			InstallerScope->SetConfigs(Configs);
		}
		InstallerScope->Configure(InstallerContainer);
		FFactoriesLocator::SetContainer(InstallerContainer);
		InstallerSubsystem->InstallerContainer = InstallerContainer;
		InstallerSubsystem->InstallerScope = InstallerScope;
		InstallerContainer->Register<UTickService>();
	}
	else
	{
		InstallerContainer = InstallerSubsystem->InstallerContainer;
	}
}

void AInstallerGameMode::InitializeInjectables()
{
	auto Injectables = InstallerContainer->ResolveAllImplements<IInjectable>();
	for (auto Injectable : Injectables)
	{
		Injectable->Inject(InstallerContainer);
	}
}

void AInstallerGameMode::InitializeInitializables()
{
	auto Initializables = InstallerContainer->ResolveAllImplements<IInitializable>();
	for (auto Initializable : Initializables)
	{
		Initializable->Initialize();
	}
}

void AInstallerGameMode::InitializeWorldables()
{
	auto Worldables = InstallerContainer->ResolveAllImplements<IWorldable>();
	if (auto InWorld = GetWorld())
	{
		for (auto Worldable : Worldables)
		{
			Worldable->WorldChanged(InWorld);
		}
	}
}

void AInstallerGameMode::InitializeTickables()
{
	TickService = InstallerContainer->Resolve<UTickService>();
	auto Tickables = InstallerContainer->ResolveAllImplements<ITickable>();
	for (auto Tickable : Tickables)
	{
		TickService->RegisterTick(Tickable);
	}
}

void AInstallerGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TickService != nullptr)
	{
		TickService->OnTick(DeltaTime);
	}
}
