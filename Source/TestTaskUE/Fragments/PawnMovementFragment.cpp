// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "PawnMoveFragment.h"
#include "Base/ControllerMovable.h"
#include "Base/ControllerRotatable.h"
#include "GameFramework/Character.h"
#include "ProjectCoreRuntime/Fragments/Base/FragmentsContainer.h"

void UPawnMoveFragment::Configure(ACharacter* InCharacter)
{
	Character = InCharacter;
}

void UPawnMoveFragment::ProcessFragmentsFromContainer(UFragmentsContainer* InFragmentsContainer)
{
	if (auto Fragment = InFragmentsContainer->TryGetFragmentInterface<IControllerMovable>())
	{
		InputMovable = Fragment;
	}
	if (auto Fragment = InFragmentsContainer->TryGetFragmentInterface<IControllerRotatable>())
	{
		InputRotatable = Fragment;
	}
}

void UPawnMoveFragment::OnTick(float DeltaSeconds)
{
	if (InputMovable != nullptr)
	{
		Move(InputMovable->GetMoveDirection());
	}
	if (InputRotatable != nullptr)
	{
		Rotate(InputRotatable->GetRotateDirection());
	}
}

void UPawnMoveFragment::Move(const FVector2D& InMoveDirection)
{
	Character->AddMovementInput(Character->GetActorForwardVector(), InMoveDirection.Y);
	Character->AddMovementInput(Character->GetActorRightVector(), InMoveDirection.X);
}

void UPawnMoveFragment::Rotate(const FVector2D& InRotateDirection)
{
	Character->AddControllerYawInput(InRotateDirection.X);
	Character->AddControllerPitchInput(InRotateDirection.Y);
}
