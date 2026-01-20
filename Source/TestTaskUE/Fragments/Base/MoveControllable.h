// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MoveControllable.generated.h"

UINTERFACE()
class UMoveControllable : public UInterface
{
	GENERATED_BODY()
};

class TESTTASKUE_API IMoveControllable
{
	GENERATED_BODY()

public:
	virtual const FVector2D& GetMoveDirection() const = 0;
};
