// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectInstallerScope.h"

#include "ProjectCoreRuntime/Configs/Base/Config.h"
#include "ProjectCoreRuntime/Configs/Base/Configs.h"
#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "ProjectCoreRuntime/Factories/PoolsFactory.h"
#include "ProjectCoreRuntime/Factories/ScreensFactory.h"
#include "ProjectCoreRuntime/Factories/ViewModelsFactory.h"
#include "ProjectCoreRuntime/Factories/ViewsFactory.h"
#include "ProjectCoreRuntime/SaveStates/HistorySaveState.h"
#include "ProjectCoreRuntime/Services/HistoryService.h"
#include "ProjectCoreRuntime/Services/LevelsService.h"
#include "ProjectCoreRuntime/Services/PreloadsService.h"
#include "ProjectCoreRuntime/Services/SavingService.h"
#include "ProjectCoreRuntime/Services/ScreensService.h"
#include "ProjectCoreRuntime/Services/TweensService.h"


void UProjectInstallerScope::RegisterConfigs()
{
	for (const auto Config : Configs->Configs)
	{
		Register(Config);
	}
}

void UProjectInstallerScope::RegisterTableConfigs()
{
	for (auto TableConfig : Configs->TableConfigs)
	{
		Container->RegisterTableConfig(TableConfig);
	}
}

void UProjectInstallerScope::RegisterSaveStates()
{
	Register<UHistorySaveState>();
}

void UProjectInstallerScope::RegisterFactories()
{
	Register<UViewModelsFactory>();
	Register<UScreensFactory>();
	Register<UHandlersFactory>();
	Register<UPoolsFactory>();
	Register<UFragmentsFactory>();
	Register<UViewsFactory>();
}

void UProjectInstallerScope::RegisterServices()
{
	Register<UAssetsService>();
	Register<USavingService>();
	Register<UScreensService>();
	Register<ULevelsService>();
	Register<UHandlersService>();
	Register<UHistoryService>();
	Register<UPreloadsService>();
	Register<UTweensService>();
}
