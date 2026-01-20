// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "GameplayGameMode.h"

#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "TestTaskUE/Handlers/PlayerHandler.h"


void AGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitializeScope();
	InitializeWorldables();
	InitializeTickables();
	
	auto HandlersFactory = InstallerContainer->Resolve<UHandlersFactory>();
	HandlersFactory->SpawnCharacterHandler<APlayerHandler>(PlayerTag);
}
