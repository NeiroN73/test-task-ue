// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHandler.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Fragments/Base/FragmentsContainer.h"
#include "TestTaskUE/Configs/InputConfig.h"
#include "TestTaskUE/Fragments/InputFragment.h"
#include "TestTaskUE/Fragments/MovementFragment.h"


APlayerHandler::APlayerHandler()
{
}

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

		// вызываем здесь, чтобы прокинуть контроллер
		if (Controller)
		{
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
	//PlayerConfig = Container->Resolve<UPlayerConfig>();
}

void APlayerHandler::BuildFragments(UFragmentsContainer* FragmentsContainer)
{
	if (auto Fragment = FragmentsContainer->TryAddFragment<UInputFragment>())
	{
		Fragment->Configure(EnhancedInputComponent);
	}
	if (auto Fragment = FragmentsContainer->TryAddFragment<UMovementFragment>())
	{
		Fragment->Configure(FragmentsContainer, this);
	}
}

