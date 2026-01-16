// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/DependencyInjection/InstallerScope.h"

#include "ProjectInstallerScope.generated.h"

UCLASS()
class TESTTASKUE_API UProjectInstallerScope : public UInstallerScope
{
	GENERATED_BODY()

public:
	virtual void RegisterConfigs() override;
	virtual void RegisterSaveStates() override;
	virtual void RegisterTableConfigs() override;
	virtual void RegisterServices() override;
	virtual void RegisterFactories() override;
};
