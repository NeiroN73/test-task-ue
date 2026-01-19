// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TestTaskUE/Configs/ElevatorsJsonConfig.h"
#include "ElevatorPreviewComponent.generated.h"

struct FGameplayTag;
class UElevatorsJsonConfig;

UCLASS()
class TESTTASKUE_API UElevatorPreviewComponent : public USceneComponent
{
	GENERATED_BODY()

#if WITH_EDITORONLY_DATA
private:
	UPROPERTY(EditAnywhere, Category = "Elevator Preview")
	TObjectPtr<UElevatorsJsonConfig> ElevatorsJsonConfig;

	UPROPERTY(EditAnywhere, Category = "Elevator Preview")
	FGameplayTag ElevatorTag;

	FStagedMoveParams StagedMoveParams;

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	UElevatorPreviewComponent();
#endif
};
