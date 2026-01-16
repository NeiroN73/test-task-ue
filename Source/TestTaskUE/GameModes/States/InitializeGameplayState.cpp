// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "InitializeGameplayState.h"

#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "TestTaskUE/Handlers/PlayerHandler.h"

void UInitializeGameplayState::Enter()
{

	
	StateMachine->NextState();
}
