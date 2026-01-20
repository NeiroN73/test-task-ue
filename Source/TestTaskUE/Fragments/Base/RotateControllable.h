// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RotateControllable.generated.h"

UINTERFACE()
class URotateControllable : public UInterface
{
	GENERATED_BODY()
};

class TESTTASKUE_API IRotateControllable
{
	GENERATED_BODY()

public:
	virtual const FVector2D& GetRotateDirection() const = 0;
};
