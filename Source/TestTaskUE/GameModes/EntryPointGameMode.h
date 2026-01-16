// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/GameModes/Base/InstallerGameMode.h"
#include "EntryPointGameMode.generated.h"

class UConfigs;

UCLASS()
class TESTTASKUE_API AEntryPointGameMode : public AInstallerGameMode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfigs> Configs;
	
	virtual void BeginPlay() override;
};
