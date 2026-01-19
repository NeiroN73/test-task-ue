// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "EntryPointGameMode.h"

#include "ProjectCoreRuntime/Configs/LevelsConfig.h"
#include "ProjectCoreRuntime/DependencyInjection/FactoriesLocator.h"
#include "ProjectCoreRuntime/Installer/InstallerGameSubsystem.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Installer/StateMachine/States/StartGameplayState.h"
#include "ProjectCoreRuntime/Interfaces/Initializable.h"
#include "ProjectCoreRuntime/Services/TickService.h"
#include "ProjectCoreRuntime/Services/Base/Tickable.h"
#include "TestTaskUE/Scopes/ProjectInstallerScope.h"

void AEntryPointGameMode::BeginPlay()
{
	Super::BeginPlay();

	auto InstallerSubsystem = GetGameInstance()->GetSubsystem<UInstallerGameSubsystem>();
	
	auto Scope = NewObject<UProjectInstallerScope>();
	Scope->SetConfigs(Configs);
	InstallerContainer = NewObject<UInstallerContainer>();
	InstallerContainer->Register(StateMachine);
	Scope->Configure(InstallerContainer);
	FFactoriesLocator::SetContainer(InstallerContainer);
	InstallerSubsystem->InstallerContainer = InstallerContainer;

	InstallerContainer->Register<UTickService>();
	TickService = InstallerContainer->Resolve<UTickService>();
	
	auto Container = InstallerContainer;
	
	StateMachine = NewObject<UInstallerStateMachine>();
	InstallerSubsystem->StateMachine = StateMachine;
	
	auto Injectables = Container->ResolveAllImplements<IInjectable>();
	for (auto Injectable : Injectables)
	{
		Injectable->Inject(Container);
	}
	auto Initializables = Container->ResolveAllImplements<IInitializable>();
	for (auto Initializable : Initializables)
	{
		Initializable->Initialize();
	}
	auto Worldables = Container->ResolveAllImplements<IWorldable>();
	if (auto InWorld = GetWorld())
	{
		for (auto Worldable : Worldables)
		{
			Worldable->WorldChanged(InWorld);
		}
	}
	auto Tickables = Container->ResolveAllImplements<ITickable>();
	for (auto Tickable : Tickables)
	{
		TickService->RegisterTick(Tickable);
	}

	auto LevelsService = InstallerContainer->Resolve<ULevelsService>();
	auto LevelsConfig = LevelsService->GetLevelsConfig();
	auto Level = LevelsConfig->GetLevel(ELevelNames::Gameplay);
	LevelsService->LoadLevelAsync(Level);
}

void AEntryPointGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickService->OnTick(DeltaTime);
}
