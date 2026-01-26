// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Base/InstallerGameMode.h"
#include "GameplayGameMode.generated.h"

class AElevatorHandler;
class UTickService;

UCLASS()
class TESTTASKUE_API AGameplayGameMode : public AInstallerGameMode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FGameplayTag PlayerTag;

	UPROPERTY(EditAnywhere)
	AElevatorHandler* ElevatorHandler;
	FTimerHandle ElevatorTimerHandle;
	void PrintElevatorState();

public:
	virtual void BeginPlay() override;
};
