// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Fragments/Base/Fragment.h"
#include "ProjectCoreRuntime/Interfaces/PreInitializable.h"
#include "MovementFragment.generated.h"

class UFragmentsContainer;

UCLASS()
class TESTTASKUE_API UMovementFragment : public UFragment,
public IPreInitializable
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TWeakObjectPtr<UFragmentsContainer> FragmentsContainer;
	UPROPERTY()
	TWeakObjectPtr<ACharacter> Character;
	
	void Move(const FVector2D& InMoveDirection);
	void Rotate(const FVector2D& InRotateDirection);

public:
	void Configure(UFragmentsContainer* InFragmentsContainer, ACharacter* InCharacter);
	virtual void PreInitialize() override;
};
