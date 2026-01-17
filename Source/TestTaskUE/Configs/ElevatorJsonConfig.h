// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Configs/Base/JsonConfig.h"
#include "ProjectCoreRuntime/Utils/JsonStructSerializer.h"
#include "ElevatorJsonConfig.generated.h"

USTRUCT()
struct FElevatorParams : public FJsonParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Duration;
};

UCLASS()
class TESTTASKUE_API UElevatorJsonConfig : public UJsonConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FElevatorParams ElevatorParams;

	virtual void ReadJson() override;
	virtual void WriteJson() override;
};
