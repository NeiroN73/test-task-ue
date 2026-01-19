// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ControllerMovable.generated.h"

UINTERFACE()
class UControllerMovable : public UInterface
{
	GENERATED_BODY()
};

class TESTTASKUE_API IControllerMovable
{
	GENERATED_BODY()

public:
	virtual const FVector2D& GetMoveDirection() const = 0;
};
