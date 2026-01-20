// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "PawnMoveFragment.h"
#include "Base/MoveControllable.h"
#include "Base/RotateControllable.h"
#include "GameFramework/Character.h"
#include "ProjectCoreRuntime/Fragments/Base/FragmentsContainer.h"

void UPawnMoveFragment::Configure(ACharacter* InCharacter)
{
	Character = InCharacter;
}

void UPawnMoveFragment::InitializeFragments(UFragmentsContainer* InFragmentsContainer)
{
	if (auto Fragment = InFragmentsContainer->TryGetFragmentInterface<IMoveControllable>())
	{
		InputMovable = Fragment;
	}
	if (auto Fragment = InFragmentsContainer->TryGetFragmentInterface<IRotateControllable>())
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
