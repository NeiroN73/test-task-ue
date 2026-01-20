// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StagedMovable.generated.h"

UENUM()
enum class EStagedMoveState : uint8
{
	IdleAtStart,
	IdleAtEnd,
	Moving
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateChanged, EStagedMoveState StagedMoveState);

UINTERFACE()
class UStagedMovable : public UInterface
{
	GENERATED_BODY()
};

class TESTTASKUE_API IStagedMovable
{
	GENERATED_BODY()
	
public:
	virtual FOnStateChanged& GetOnStateChangedDelegate() = 0;
	virtual EStagedMoveState GetCurrentMoveState() const = 0;
};
