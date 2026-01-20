// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "EntryPointGameMode.h"

#include "ProjectCoreRuntime/Configs/LevelsConfig.h"
#include "ProjectCoreRuntime/Installer/StateMachine/States/StartGameplayState.h"
#include "TestTaskUE/Scopes/ProjectInstallerScope.h"

void AEntryPointGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitializeScope(Configs);
	InitializeInjectables();
	InitializeInitializables();
	InitializeWorldables();
	InitializeTickables();
	
	auto LevelsService = InstallerContainer->Resolve<ULevelsService>();
	auto LevelsConfig = LevelsService->GetLevelsConfig();
	auto Level = LevelsConfig->GetLevel(ELevelNames::Gameplay);
	LevelsService->LoadLevelAsync(Level);
}
