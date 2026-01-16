// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/GameModes/Base/InstallerGameMode.h"
#include "GameplayGameMode.generated.h"

UCLASS()
class TESTTASKUE_API AGameplayGameMode : public AInstallerGameMode
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
};
