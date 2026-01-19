// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "PlayerControllerFragment.h"

#include "EnhancedInputComponent.h"
#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "TestTaskUE/Configs/InputConfig.h"

void UPlayerControllerFragment::Configure(UEnhancedInputComponent* InEnhancedInputComponent)
{
	EnhancedInputComponent = InEnhancedInputComponent;
}

const FVector2D& UPlayerControllerFragment::GetMoveDirection() const
{
	return MoveInputDirection;
}

const FVector2D& UPlayerControllerFragment::GetRotateDirection() const
{
	return RotateInputDirection;
}

void UPlayerControllerFragment::Inject(UInstallerContainer* InContainer)
{
	InputConfig = InContainer->Resolve<UInputConfig>();
}

void UPlayerControllerFragment::Initialize()
{
	EnhancedInputComponent->BindActionValueLambda(InputConfig->MoveAction, ETriggerEvent::Triggered,
	[this](const FInputActionValue& Value)
	{
		MoveInputDirection = Value.Get<FVector2D>();
	});

	EnhancedInputComponent->BindActionValueLambda(InputConfig->MoveAction, ETriggerEvent::Completed,
	[this](const FInputActionValue& Value)
	{
		MoveInputDirection = FVector2D::Zero();
	});

	EnhancedInputComponent->BindActionValueLambda(InputConfig->LookAction, ETriggerEvent::Triggered,
	[this](const FInputActionValue& Value)
	{
		RotateInputDirection = Value.Get<FVector2D>();
	});

	EnhancedInputComponent->BindActionValueLambda(InputConfig->LookAction, ETriggerEvent::Completed,
[this](const FInputActionValue& Value)
	{
		RotateInputDirection = FVector2D::Zero();
	});
}