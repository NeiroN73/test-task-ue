// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ProjectCoreRuntime/Configs/Base/JsonConfig.h"
#include "ProjectCoreRuntime/Services/Base/TweensTypes.h"
#include "ProjectCoreRuntime/Utils/JsonStructSerializer.h"
#include "ElevatorsJsonConfig.generated.h"

USTRUCT()
struct FStagedMoveStageParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Duration;
	UPROPERTY(EditAnywhere)
	ETweenEaseType EaseType;
};

USTRUCT()
struct FStagedMoveParams : public FJsonParams
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere)
	FVector Position;
	
	UPROPERTY(EditAnywhere)
	TArray<FStagedMoveStageParams> Stages;
};

USTRUCT()
struct FStagedMovesParams : public FJsonParams
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<FStagedMoveParams> ElevatorsByTag;
};

UCLASS()
class TESTTASKUE_API UElevatorsJsonConfig : public UJsonConfig
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FStagedMovesParams Elevators;
	
public:
	const FStagedMoveParams* GetElevatorParamsByTag(FGameplayTag InTag) const;

protected:
	virtual void ReadJson() override;
	virtual void WriteJson() override;
};
