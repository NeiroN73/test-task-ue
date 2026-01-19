// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ControllerRotatable.generated.h"

UINTERFACE()
class UControllerRotatable : public UInterface
{
	GENERATED_BODY()
};

class TESTTASKUE_API IControllerRotatable
{
	GENERATED_BODY()

public:
	virtual const FVector2D& GetRotateDirection() const = 0;
};
