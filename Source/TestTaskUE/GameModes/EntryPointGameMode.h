// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/GameModes/Base/InstallerGameMode.h"
#include "EntryPointGameMode.generated.h"

class UTickService;
class UInstallerContainer;
class UInstallerStateMachine;
class UConfigs;

UCLASS()
class TESTTASKUE_API AEntryPointGameMode : public AInstallerGameMode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfigs> Configs;
	
	UPROPERTY()
	TObjectPtr<UInstallerStateMachine> StateMachine;
	UPROPERTY()
	TObjectPtr<UInstallerContainer> InstallerContainer;
	UPROPERTY()
	TWeakObjectPtr<UTickService> TickService;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
