// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InstallerGameMode.generated.h"

class UProjectInstallerScope;
class UConfigs;
class UTickService;
class UInstallerContainer;

UCLASS()
class TESTTASKUE_API AInstallerGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UInstallerContainer> InstallerContainer;
	UPROPERTY()
	TWeakObjectPtr<UTickService> TickService;
	
	void InitializeScope(UConfigs* Configs = nullptr);
	void InitializeInjectables();
	void InitializeInitializables();
	void InitializeWorldables();
	void InitializeTickables();
	
public:
	AInstallerGameMode();
	virtual void Tick(float DeltaTime) override;
};
