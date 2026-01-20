// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Fragments/Base/Fragment.h"
#include "ProjectCoreRuntime/Services/Base/Tickable.h"
#include "PawnMoveFragment.generated.h"

class IRotateControllable;
class IMoveControllable;
class UFragmentsContainer;

UCLASS()
class TESTTASKUE_API UPawnMoveFragment : public UFragment,
public ITickable
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TWeakObjectPtr<ACharacter> Character;
	TWeakInterfacePtr<IMoveControllable> InputMovable;
	TWeakInterfacePtr<IRotateControllable> InputRotatable;
	
	void Move(const FVector2D& InMoveDirection);
	void Rotate(const FVector2D& InRotateDirection);

public:
	void Configure(ACharacter* InCharacter);
	virtual void InitializeFragments(UFragmentsContainer* InFragmentsContainer) override;
	virtual void OnTick(float DeltaSeconds) override;
};
