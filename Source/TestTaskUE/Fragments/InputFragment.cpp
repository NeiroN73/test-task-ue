// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "InputFragment.h"

#include "EnhancedInputComponent.h"
#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "TestTaskUE/Configs/InputConfig.h"

void UInputFragment::Configure(UEnhancedInputComponent* InEnhancedInputComponent)
{
	EnhancedInputComponent = InEnhancedInputComponent;
}

void UInputFragment::Inject(UInstallerContainer* InContainer)
{
	InputConfig = InContainer->Resolve<UInputConfig>();
}

void UInputFragment::Initialize()
{
	EnhancedInputComponent->BindActionValueLambda(InputConfig->MoveAction, ETriggerEvent::Triggered,
	[this](const FInputActionValue& Value)
	{
		auto MovementVector = Value.Get<FVector2D>();
		OnMoveVectorChanged.Broadcast(MovementVector);
	});

	EnhancedInputComponent->BindActionValueLambda(InputConfig->MoveAction, ETriggerEvent::Completed,
	[this](const FInputActionValue& Value)
	{
		auto MovementVector = FVector2D::Zero();
		OnMoveVectorChanged.Broadcast(MovementVector);
	});

	EnhancedInputComponent->BindActionValueLambda(InputConfig->LookAction, ETriggerEvent::Triggered,
	[this](const FInputActionValue& Value)
	{
		auto RotateVector = Value.Get<FVector2D>();
		OnRotateVectorChanged.Broadcast(RotateVector);
	});
}