// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "MovementFragment.h"

#include "InputFragment.h"
#include "GameFramework/Character.h"
#include "ProjectCoreRuntime/Fragments/Base/FragmentsContainer.h"

void UMovementFragment::PreInitialize()
{
	if (auto Fragment = FragmentsContainer->TryGetFragment<UInputFragment>())
	{
		Fragment->OnMoveVectorChanged.AddUObject(this, &UMovementFragment::Move);
		Fragment->OnRotateVectorChanged.AddUObject(this, &UMovementFragment::Rotate);
	}
}

void UMovementFragment::Move(const FVector2D& InMoveDirection)
{
	Character->AddMovementInput(Character->GetActorForwardVector(), InMoveDirection.Y);
	Character->AddMovementInput(Character->GetActorRightVector(), InMoveDirection.X);
}

void UMovementFragment::Rotate(const FVector2D& InRotateDirection)
{
	Character->AddControllerYawInput(InRotateDirection.X);
	Character->AddControllerPitchInput(InRotateDirection.Y);
}

void UMovementFragment::Configure(UFragmentsContainer* InFragmentsContainer, ACharacter* InCharacter)
{
	FragmentsContainer = InFragmentsContainer;
	Character = InCharacter;
}
