// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Fragments/Base/Fragment.h"
#include "ProjectCoreRuntime/Interfaces/Initializable.h"
#include "StagedActorMoveFragment.generated.h"

class UFragmentsContainer;

UCLASS()
class TESTTASKUE_API UStagedActorMoveFragment : public UFragment,
public IInitializable
{
	GENERATED_BODY()

public:
	virtual void ProcessFragmentsFromContainer(UFragmentsContainer* InFragmentsContainer) override;
	virtual void Initialize() override;
};
