// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstallerGameMode.h"
#include "EntryPointGameMode.generated.h"

class UTickService;
class UInstallerContainer;
class UInstallerStateMachine;
class UConfigs;

UCLASS()
class TESTTASKUE_API AEntryPointGameMode : public AInstallerGameMode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfigs> Configs;

public:
	virtual void BeginPlay() override;
};
