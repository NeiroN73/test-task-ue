// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/GameModes/Base/InstallerGameMode.h"
#include "GameplayGameMode.generated.h"

class UTickService;

UCLASS()
class TESTTASKUE_API AGameplayGameMode : public AInstallerGameMode
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TWeakObjectPtr<UTickService> TickService;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
