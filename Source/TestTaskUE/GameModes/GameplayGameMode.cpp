// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "GameplayGameMode.h"

#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "ProjectCoreRuntime/Fragments/Base/FragmentsContainer.h"
#include "ProjectCoreRuntime/Services/HandlersService.h"
#include "TestTaskUE/Fragments/Base/StagedMovable.h"
#include "TestTaskUE/Handlers/ElevatorHandler.h"
#include "TestTaskUE/Handlers/PlayerHandler.h"


void AGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitializeScope();
	InitializeWorldables();
	InitializeTickables();
	
	auto HandlersFactory = InstallerContainer->Resolve<UHandlersFactory>();
	HandlersFactory->SpawnCharacterHandler<APlayerHandler>(PlayerTag);

	ElevatorHandler = InstallerContainer->Resolve<UHandlersService>()->
			GetActorHandler<AElevatorHandler>(FGameplayTag::RequestGameplayTag("Elevators.Elevator1"));
    
	PrintElevatorState();
	GetWorldTimerManager().SetTimer(ElevatorTimerHandle, this, &AGameplayGameMode::PrintElevatorState, 1.0f, true);
}

void AGameplayGameMode::PrintElevatorState()
{
	if (ElevatorHandler)
	{
		if (auto StagedMovable = ElevatorHandler->GetFragmentsContainer()->TryGetFragmentInterface<IStagedMovable>())
		{
			auto State = StagedMovable->GetCurrentMoveState();
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Yellow, 
					FString::Printf(TEXT("[%s] State: %d"), *FDateTime::Now().ToString(TEXT("%H:%M:%S")), 
					State));
		}
	}
}
