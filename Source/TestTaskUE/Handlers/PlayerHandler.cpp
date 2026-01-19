// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHandler.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Fragments/Base/FragmentsContainer.h"
#include "TestTaskUE/Configs/InputConfig.h"
#include "TestTaskUE/Fragments/PlayerControllerFragment.h"
#include "TestTaskUE/Fragments/PawnMoveFragment.h"


void APlayerHandler::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if (APlayerController* InPlayerController = Cast<APlayerController>(Controller))
	{
		PlayerController = InPlayerController;
		
		if (auto Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(InPlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputConfig->PlayerMappingContext, 0);
		}
	}
}

void APlayerHandler::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* InEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent = InEnhancedInputComponent;
	}
}

void APlayerHandler::Inject(UInstallerContainer* Container)
{
	InputConfig = Container->Resolve<UInputConfig>();
}

void APlayerHandler::BuildFragments(UFragmentsContainer* FragmentsContainer)
{
	if (auto Fragment = FragmentsContainer->TryAddFragmentByInterfaces<UPlayerControllerFragment>(
		{UControllerMovable::StaticClass(), UControllerRotatable::StaticClass()}))
	{
		Fragment->Configure(EnhancedInputComponent);
	}
	if (auto Fragment = FragmentsContainer->TryAddFragment<UPawnMoveFragment>())
	{
		Fragment->Configure(this);
	}
}

